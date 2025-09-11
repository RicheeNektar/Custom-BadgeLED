#ifndef WIFICONFIG_H
#define WIFICONFIG_H

#include <WString.h>

#include "Abstract.h"

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

    static String getContextName() {
        return "wifi";
    }

    void serialize(const File& file) const override;
    static WifiConfig* deserialize(const File &file);
};

#endif //WIFICONFIG_H
