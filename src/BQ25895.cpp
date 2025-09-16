#include "BQ25895.h"
#include "Logs.h"
#include "LEDS.h"

#include <Wire.h>
#include <Arduino.h>

void BQ25895::init() {
    Wire.begin(SDA_PIN, SCL_PIN, I2C_FREQUENCY);
    Wire.setTimeOut(200); // ms

    if (!tryConnect()) {
        Logs::error("Could not connect!", ERROR_BQ25985_CONNECT_FAULT, ERROR_MODULE_BQ25985);
        return;
    }

    // Set input current
    if (writeRegister(REG_00_INPUT_SOURCE_CTRL, 0x30 /* 1500mA */)) {
        Logs::error("Could not set IN current", ERROR_BQ25985_SET_IN_CURRENT, ERROR_MODULE_BQ25985);
    }

    // ADC
    if (!writeRegister(REG_07_MONITOR_CTRL, 0x95)) {
        Logs::error("Could not enable ADC", ERROR_BQ25985_ADC, ERROR_MODULE_BQ25985);
    }

    // Thermal safety
    if (!writeRegister(REG_06_IR_COMP_THERM_CTRL, 0x32)) {
        Logs::error("Could not enable TS", ERROR_BQ25985_THERMAL_SENSE, ERROR_MODULE_BQ25985);
    }

    // Disable JEITA
    if (!writeRegister(REG_05_CHARGE_TERM_TIMER, 0x00)) {
        Logs::error("Could not disable JEITA", ERROR_BQ25985_JEITA, ERROR_MODULE_BQ25985);
    }

    // Set SYS min voltage
    if (!writeRegister(REG_03_PRECHG_TERM_CURRENT, 0x1A /* 3.3V */)) {
        Logs::error("Could not set SYS min V", ERROR_BQ25985_SYS_MIN_V, ERROR_MODULE_BQ25985);
    }

    // Disable safety timer
    if (!writeRegister(REG_01_POWER_ON_CONFIG, 0x3C)) {
        Logs::error("Could not disable safety timer", ERROR_BQ25985_SAFETY_TIMER, ERROR_MODULE_BQ25985);
    }

    // Disable watchdog
    if (!writeRegister(REG_08_SYS_FUNCTION_CTRL, 0x7A)) {
        Logs::error("Could not disable watchdog", ERROR_BQ25985_WATCHDOG, ERROR_MODULE_BQ25985);
    }

    // Disable stat-pin blink
    const uint8_t reg0A = readRegister(REG_0A_MISC_OPERATION_CTRL);
    if (reg0A != 0xFF) {
        if (!writeRegister(REG_0A_MISC_OPERATION_CTRL, reg0A &~ 0x08)) {
            Logs::error("Could not disable stat-pin blink", ERROR_BQ25985_STAT_PIN_BLINK, ERROR_MODULE_BQ25985);
        }
    }
}

bool BQ25895::setChargeCurrent(const uint8_t current) {
    return writeRegister(REG_02_CHARGE_CURRENT_CTRL, current);
}

bool BQ25895::tryConnect() {
    try {
        Wire.beginTransmission(BQ25895_ADDRESS);
        return 0 == Wire.endTransmission();
    } catch (...) {
        return false;
    }
}

bool BQ25895::isVBUSPresent() {
    const uint8_t stat = readRegister(REG_08_SYS_FUNCTION_CTRL);
    return stat != 0xFF
        && stat  & 0xE0;
}

bool BQ25895::writeRegister(const uint8_t reg, const uint8_t value) {
    try {
        Wire.beginTransmission(BQ25895_ADDRESS);
        Wire.write(reg);
        Wire.write(value);

        const byte error = Wire.endTransmission();
        if (error != 0) {
            Logs::addf("Could not write to REG 0x%02X: %d", reg, error);
            return false;
        }
    } catch (std::exception& e) {
        Logs::addf("Could not write to REG 0x%02X: %s", reg, e.what());
        return false;
    }

    return true;
}

uint8_t BQ25895::readRegister(const uint8_t reg) {
    Wire.beginTransmission(BQ25895_ADDRESS);
    Wire.write(reg);

    const uint8_t error = Wire.endTransmission(false);
    if (error != 0) {
        return 0xFF;
    }

    Wire.requestFrom(static_cast<uint8_t>(BQ25895_ADDRESS), static_cast<uint8_t>(1));

    if (!Wire.available()) {
        return 0xFF;
    }

    return Wire.read();
}

ChargeStatus BQ25895::getChargeStatus() {
    const uint8_t status = readRegister(REG_0B_SYSTEM_STATUS);
    if (status == 0xFF) {
        return CHARGE_STATUS_UNKNOWN;
    }

    const uint8_t chargeStatus = status >> 6 & 0x03;
    switch (chargeStatus) {
        case 0:
            return CHARGE_STATUS_DISCHARGING;
        case 1:
            return CHARGE_STATUS_PRE_CHARGING;
        case 2:
            return CHARGE_STATUS_CHARGING;
        case 3:
            return CHARGE_STATUS_DONE;
        default:
            Logs::addf("Unknown status %02X", status);
            return CHARGE_STATUS_UNKNOWN;
    }
}

Temperature BQ25895::getTemperature() {
    const uint8_t status = readRegister(REG_0B_SYSTEM_STATUS);

    switch (status) {
        case 0:
            return TEMPERATURE_REGULAR;
        case 1:
            return TEMPERATURE_FREEZING;
        case 2:
            return TEMPERATURE_COLD;
        case 3:
            return TEMPERATURE_HOT;
        case 4:
            return TEMPERATURE_CRITICAL;
        default:
            Logs::addf("Unknown status %02X", status);
            // Fallthrough
        case 0xFF:
            return TEMPERATURE_UNKNOWN;
    }
}

float BQ25895::getTemperatureFloat() {
    const uint8_t msb = readRegister(REG_18_ADC_DIE_TEMP_MSB);
    const uint8_t lsb = readRegister(REG_19_ADC_DIE_TEMP_LSB);

    if (msb == 0xFF || lsb == 0xFF) {
        return -1.0f;
    }

    const uint16_t raw = msb << 8 | lsb;
    return 0.465f * raw - 273.15f; // 0.465°C pro LSB, Offset -273.15°C
}
