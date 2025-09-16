#include "wifi/AccessPoint.h"

#include <WiFi.h>
#include <ESPmDNS.h>

#include "Globals.h"
#include "Logs.h"

bool AccessPoint::restart() {
    delete wifiConfig;
    wifiConfig = WifiConfig::load();

    if (wifiConfig == nullptr) {
        Logs::errorf(ERROR_AP_INIT, ERROR_MODULE_AP, "Failed to load config");
        return WiFi.softAP(
            "LED-Badge fallback",
            nullptr
        );
    }

    if (wifiConfig->enabled) {
        return WiFi.softAP(
            wifiConfig->ssid,
            wifiConfig->password
        );
    }

    return true;
}

bool AccessPoint::init() {
    return restart()
        && MDNS.begin("badge");
}

WifiConfig* wifiConfig = nullptr;
