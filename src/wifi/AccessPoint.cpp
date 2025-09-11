#include "wifi/AccessPoint.h"

#include <WiFi.h>

void AccessPoint::restart() {
    WiFi.softAPdisconnect(true);
    delete wifiConfig;
    init();
}

bool AccessPoint::init() {
    wifiConfig = WifiConfig::load();

    if (wifiConfig->enabled) {
        WiFi.softAPsetHostname("badge.local");
        return WiFi.softAP(
            wifiConfig->ssid,
            wifiConfig->password
        );
    }

    return true;
}

AccessPoint AP;
WifiConfig* wifiConfig = nullptr;
