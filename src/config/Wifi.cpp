#include "config/Wifi.h"

WifiConfig* WifiConfig::standard() {
    return new WifiConfig(
        true,
        "LED-Badge",
        ""
    );
}

WifiConfig* WifiConfig::deserialize(File& file) {
    uint8_t sizes[2];
    file.read(sizes, sizeof(sizes));

    uint8_t enabled;

    file.read(&enabled, 1);

    uint8_t* ssid = new uint8_t[sizes[0] + 1];
    file.read(ssid, sizes[0]);
    ssid[sizes[0]] = '\0';

    uint8_t* pass = nullptr;
    if (sizes[1] == 0) {
        pass = new uint8_t[sizes[1] + 1];
        file.read(pass, sizes[1]);
        pass[sizes[1]] = '\0';
    }

    return new WifiConfig(
        enabled > 0,
        reinterpret_cast<const char*>(ssid),
        reinterpret_cast<const char*>(pass)
    );
}

void WifiConfig::serialize(File& file) const {
    const uint8_t ssidLen = strlen(this->ssid);
    const uint8_t passLen = strlen(this->password);

    // prop lengths
    file.write(ssidLen);
    file.write(passLen);

    // props
    file.write(this->enabled);
    file.write(reinterpret_cast<const uint8_t*>(this->ssid), ssidLen);
    file.write(reinterpret_cast<const uint8_t*>(this->password), passLen);
}
