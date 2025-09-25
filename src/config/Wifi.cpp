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

void WifiConfig::deserialize(File& file) {
    file.read(reinterpret_cast<uint8_t*>(&enabled), 1);
    ssid = readString(file);
    password = readString(file);
}

void WifiConfig::serialize(File& file) const {
    file.write(reinterpret_cast<const uint8_t*>(&enabled), 1);
    writeString(file, ssid);
    writeString(file, password);
}
