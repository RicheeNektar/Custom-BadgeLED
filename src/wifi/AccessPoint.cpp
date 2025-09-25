#include "wifi/AccessPoint.h"
#include "config/Wifi.h"

#include <WiFi.h>
#include <ESPmDNS.h>

bool AccessPoint::restart() {
    MDNS.end();
    WiFi.softAPdisconnect(true);

    if (wifiConfig.enabled) {
        return WiFi.softAP(
            wifiConfig.ssid,
            wifiConfig.password
        ) && MDNS.begin("badge");
    }

    return true;
}

bool AccessPoint::init() {
    wifiConfig.load();
    return restart();
}
