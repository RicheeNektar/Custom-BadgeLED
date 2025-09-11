#ifndef AP_H
#define AP_H

#include "config/Wifi.h"

struct AP {
    static void restart();

    static bool init();
};

extern WifiConfig* wifiConfig;

#endif //AP_H
