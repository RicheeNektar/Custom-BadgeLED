#ifndef BQ25895_H
#define BQ25895_H

#include <cstdint>

// I2C Pins
#define SDA_PIN 45
#define SCL_PIN 46
#define INT_PIN 3

// BQ25895 I2C Adresse
#define BQ25895_ADDRESS 0x6A
#define I2C_FREQUENCY 1000000 // 1.000,0 Hz

// Register Adressen
#define REG_00_INPUT_SOURCE_CTRL    0x00
#define REG_01_POWER_ON_CONFIG      0x01
#define REG_02_CHARGE_CURRENT_CTRL  0x02
#define REG_03_PRECHG_TERM_CURRENT  0x03
#define REG_04_CHARGE_VOLTAGE_CTRL  0x04
#define REG_05_CHARGE_TERM_TIMER    0x05
#define REG_06_IR_COMP_THERM_CTRL   0x06
#define REG_07_MONITOR_CTRL         0x07
#define REG_08_SYS_FUNCTION_CTRL    0x08
#define REG_09_OTG_CTRL             0x09
#define REG_0A_MISC_OPERATION_CTRL  0x0A
#define REG_0B_SYSTEM_STATUS        0x0B
#define REG_0C_FAULT_STATUS         0x0C
#define REG_0D_MASK_CTRL            0x0D
#define REG_0E_ADC_VBAT_MSB         0x0E
#define REG_0F_ADC_VBAT_LSB         0x0F
#define REG_10_ADC_VSYS_MSB         0x10
#define REG_11_ADC_VSYS_LSB         0x11
#define REG_12_ADC_VBUS_MSB         0x12
#define REG_13_ADC_VBUS_LSB         0x13
#define REG_14_ADC_ICHG_MSB         0x14
#define REG_15_ADC_ICHG_LSB         0x15
#define REG_16_ADC_IDPM_MSB         0x16
#define REG_17_ADC_IDPM_LSB         0x17
#define REG_18_ADC_DIE_TEMP_MSB     0x18
#define REG_19_ADC_DIE_TEMP_LSB     0x19

enum Temperature {
    TEMPERATURE_UNKNOWN,
    TEMPERATURE_FREEZING,
    TEMPERATURE_COLD,
    TEMPERATURE_REGULAR,
    TEMPERATURE_HOT,
    TEMPERATURE_CRITICAL,
};

enum ChargeStatus {
    CHARGE_STATUS_UNKNOWN,
    CHARGE_STATUS_DISCHARGING,
    CHARGE_STATUS_PRE_CHARGING,
    CHARGE_STATUS_CHARGING,
    CHARGE_STATUS_DONE,
};

class BQ25895 {
    bool lastVBUSState = false;
    int lastRequestedChargeCurrent = 0;

    static bool tryConnect();

    static bool writeRegister(uint8_t reg, uint8_t value);

    static uint8_t readRegister(uint8_t reg);

public:
    static void init();

    static bool setChargeCurrent(uint8_t current);

    static bool isVBUSPresent();

    static Temperature getTemperature();
    static float getTemperatureFloat();

    static ChargeStatus getChargeStatus();
};

#endif //BQ25895_H
