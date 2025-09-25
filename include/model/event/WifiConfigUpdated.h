#ifndef WIFI_CONFIG_UPDATED_H
#define WIFI_CONFIG_UPDATED_H

#include "AbstractEvent.h"

struct WifiConfigUpdated final : virtual AbstractEvent {
    static constexpr uint8_t id = 0x1;
};

#endif //WIFI_CONFIG_UPDATED_H
