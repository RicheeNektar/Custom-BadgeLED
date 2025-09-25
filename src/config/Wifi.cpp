#include "config/Wifi.h"

WifiConfig wifiConfig{
    true,
    "LED-Badge",
    nullptr
};

void WifiConfig::defaults() {
    this->enabled = true;
    this->ssid = "LED-Badge";
    this->password = nullptr;
}

void WifiConfig::deserialize(File& file) {
    file.read(reinterpret_cast<uint8_t*>(&this->enabled), 1);
    this->ssid = readString(file);
    this->password = readString(file);
}

void WifiConfig::serialize(File& file) const {
    file.write(reinterpret_cast<const uint8_t*>(&this->enabled), 1);
    writeString(file, this->ssid);
    writeString(file, this->password);
}
