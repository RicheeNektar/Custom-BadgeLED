#include "BQ25895.h"
#include "Logs.h"

#include <Wire.h>
#include <Arduino.h>

bool BQ25895::tryConnect() {
    try {
        Wire.beginTransmission(BQ25895_ADDRESS);
        return 0 == Wire.endTransmission();
    } catch (...) {
        Serial.println("❌ Fehler bei I2C-Kommunikation");
        Logs::add("KRITISCHER FEHLER: I2C-Kommunikation fehlgeschlagen");
        return false;
    }
}

bool BQ25895::isVBUSPresent() {
    uint8_t stat = readRegister(0x0B);
    return (stat != 0xFF && (stat & 0xE0));
}

bool BQ25895::writeRegister(uint8_t reg, uint8_t value) {
    try {
        
        Wire.beginTransmission(BQ25895_ADDRESS);
        Wire.write(reg);
        Wire.write(value);

        const byte error = Wire.endTransmission();
        if (error != 0) {
            Serial.printf("❌ I2C Fehler beim Schreiben von Register 0x%02X: %d\n", reg, error);
            return false;
        }

        Serial.printf("Register 0x%02X = 0x%02X geschrieben\n", reg, value);
        return true;
    } catch (...) {
        Logs::addf(LOG_CHANNEL_CHARGER, "Could not write to REG 0x%02X", reg);
        return false;
    }
}

uint8_t BQ25895::readRegister(uint8_t reg) {
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


