#ifndef AP_H
#define AP_H

#include "config/Wifi.h"

struct AccessPoint {
    static bool restart();

    static bool init();
};

extern WifiConfig* wifiConfig;

#endif //AP_H
