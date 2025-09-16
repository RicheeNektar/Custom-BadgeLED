#include "Main.h"
#include "Globals.h"
#include "BQ25895.h"
#include "LEDS.h"
#include "Logs.h"
#include "web/Server.h"
#include "wifi/AccessPoint.h"

#include <Arduino.h>
#include <FastLED.h>
#include <LittleFS.h>

void setup() {
    Serial.begin(115200);
    Serial.print("Pin init..");
    pinMode(BOOT_BUTTON_PIN, INPUT_PULLUP);

    pinMode(MODE_BUTTON, INPUT);
    pinMode(COLOR_BUTTON, INPUT);
    pinMode(BRIGHT_BUTTON, INPUT);
    pinMode(SAO_BUTTON, INPUT);

    pinMode(STATUS_LED_PIN, OUTPUT);
    pinMode(MAIN_LED_PIN, OUTPUT);

    pinMode(LIGHT_EN, OUTPUT);

    digitalWrite(STATUS_LED_PIN, LOW);
    digitalWrite(MAIN_LED_PIN, LOW);

    digitalWrite(LIGHT_EN, HIGH);
    Serial.println("OK!");

    // LEDs first since they can "display" error codes
    Serial.print("LEDs init..");
    LEDS::init();
    Serial.println("OK!");

    Serial.print("FS init..");
    if (LittleFS.begin()) {
        Serial.println("OK!");
    } else {
        Serial.println("ERR");
        LEDS::error(ERROR_FS_INIT, ERROR_MODULE_FS);
        return;
    }

    Logs::add("Rebooted");

    Serial.print("AP init..");
    if (AccessPoint::init()) {
        Serial.println("OK!");
    } else {
        Serial.println("ERR");
        Logs::error("AP failed", ERROR_AP_INIT, ERROR_MODULE_AP);
        return;
    }

    Serial.print("WebServer init..");
    WebServer::init();
    Serial.println("OK!");

    Serial.print("BQ25895 init..");
    BQ25895::init();
    Serial.println("OK!");
}

void loop() {
    if (animation != nullptr) {
        animation->step();
    }
    FastLED.show(STATUS_LED_BRIGHTNESS);
}