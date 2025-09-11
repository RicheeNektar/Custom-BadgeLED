#ifndef AP_H
#define AP_H

#include "config/Wifi.h"

struct AccessPoint {
    void restart();

    bool init();
};

extern AccessPoint AP;
extern WifiConfig* wifiConfig;

#endif //AP_H
