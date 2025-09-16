#ifndef WIFICONFIG_H
#define WIFICONFIG_H

#include "Abstract.h"

#include <WString.h>

struct WifiConfig final : virtual AbstractConfig<WifiConfig> {
    const bool enabled;
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

    static String getContextName() {
        return "wifi";
    }

    void serialize(File& file) const override;

    static WifiConfig* deserialize(File& file);

    static WifiConfig* standard();
};

#endif //WIFICONFIG_H
