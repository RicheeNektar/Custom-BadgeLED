#include "wifi/AP.h"

#include <WiFi.h>

void AP::restart() {
    delete wifiConfig;
    init();
}

void AP::init() {
    wifiConfig = WifiConfig::load();

    if (wifiConfig->enabled) {
        WiFi.softAP(
            wifiConfig->ssid.c_str(),
            wifiConfig->password.c_str()
        );
    }
}

WifiConfig* wifiConfig = nullptr;
