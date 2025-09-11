#include "wifi/AP.h"

#include <WiFi.h>

void AP::restart() {
    WiFi.softAPdisconnect(true);
    delete wifiConfig;
    init();
}

bool AP::init() {
    wifiConfig = WifiConfig::load();

    if (wifiConfig->enabled) {
        return WiFi.softAP(
            wifiConfig->ssid.c_str(),
            wifiConfig->password.c_str()
        );
    }

    return true;
}

WifiConfig* wifiConfig = nullptr;
