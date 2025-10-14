#include "wifi/AccessPoint.h"
#include "config/Wifi.h"
#include "web/Server.h"

#include <WiFi.h>
#include <ESPmDNS.h>

#include "LEDS.h"

bool AccessPoint::restart() {
    if (0 != WiFi.softAPIP()) {
        MDNS.end();
        WebServer::stop();
        WiFi.softAPdisconnect(true);
    }

    if (wifiConfig.enabled) {
        if (
            !WiFi.softAP(
                wifiConfig.ssid,
                wifiConfig.password
            )
        ) {
            return false;
        }

        while (0 == WiFi.softAPIP()) {
            vTaskDelay(pdMS_TO_TICKS(50));
        }

        WebServer::start();

        LEDS::status(STATUS_LED_ID_MAIN, STATUS_GREEN);
        return MDNS.begin("badge");
    }

    LEDS::status(STATUS_LED_ID_MAIN, STATUS_RED);
    return true;
}

bool AccessPoint::init() {
    wifiConfig.load();
    return restart();
}
