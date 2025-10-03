#ifndef WIFICONFIG_H
#define WIFICONFIG_H

#include "AbstractConfig.h"

struct WifiConfig final : virtual AbstractConfig {
    bool enabled;
    const char* ssid;
    const char* password;

    WifiConfig(
        const bool enabled,
        const char* ssid,
        const char* password
    ):
        enabled(enabled),
        ssid(ssid),
        password(password)
    {}

    ~WifiConfig() override {
        delete[] ssid;
        delete[] password;
    };

    const char* getContextName() override {
        return "wifi";
    }

    void serialize(Print& file) const override;

    void deserialize(Stream& file) override;

    bool validate() override;

    void defaults() override;
};

extern WifiConfig wifiConfig;

#endif //WIFICONFIG_H
