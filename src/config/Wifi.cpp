#include "config/Wifi.h"

WifiConfig wifiConfig{
    true,
    "LED-Badge",
    nullptr
};

void WifiConfig::defaults() {
    enabled = true;
    ssid = "LED-Badge";
    password = nullptr;
}

bool WifiConfig::validate() {
    return
        nullptr != ssid
        && strlen(ssid) > 0
        && (
            password == nullptr
            || strlen(password) >= 8
        )
    ;
}

void WifiConfig::deserialize(Stream& file) {
    file.readBytes(reinterpret_cast<uint8_t*>(&enabled), 1);
    ssid = readString(file);
    password = readString(file);
}

void WifiConfig::serialize(Print& file) const {
    file.write(reinterpret_cast<const uint8_t*>(&enabled), 1);
    writeString(file, ssid);
    writeString(file, password);
}
