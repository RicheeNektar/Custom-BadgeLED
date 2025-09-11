#include "Main.h"
#include <Arduino.h>

#include <FastLED.h>
#include <LittleFS.h>

#include "Globals.h"
#include "BQ25895.h"
#include "LEDS.h"
#include "web/Server.h"
#include "wifi/AccessPoint.h"

void setup() {
    pinMode(STATUS_LED_PIN, OUTPUT);
    pinMode(MAIN_LED_PIN, OUTPUT);

    pinMode(BOOT_BUTTON_PIN, INPUT_PULLUP);

    pinMode(MODE_BUTTON, INPUT);
    pinMode(COLOR_BUTTON, INPUT);
    pinMode(BRIGHT_BUTTON, INPUT);
    pinMode(SAO_BUTTON, INPUT);

    pinMode(LIGHT_EN, OUTPUT);

    digitalWrite(STATUS_LED_PIN, LOW);
    digitalWrite(MAIN_LED_PIN, LOW);

    digitalWrite(LIGHT_EN, HIGH);

    Serial.begin(115200);

    // FS first, because everything depends on it
    Serial.print("FS init..");
    if (!LittleFS.begin()) {
        Serial.println("ERR");
        return;
    }
    Serial.println("OK!");

    // Serial.print("BQ25895 init..");
    // BQ25895::init();
    // Serial.println("OK!");

    Serial.println("LEDs init..");
    LEDs.init();
    Serial.println("OK!");

    statusLeds[STATUS_LED_ID_MAIN] = CHSV(0, 255, 255);
    FastLED.show(STATUS_LED_BRIGHTNESS);

    delay(3000);

    Serial.print("AP init..");
    AP.init();
    Serial.println("OK!");

    statusLeds[STATUS_LED_ID_MAIN] = CHSV(128, 255, 255);
    FastLED.show(STATUS_LED_BRIGHTNESS);

    delay(3000);

    Serial.print("Server init..");
    WebServer::registerRoutes();
    Serial.println("OK!");

    statusLeds[STATUS_LED_ID_MAIN] = CHSV(230, 255, 255);
    FastLED.show(STATUS_LED_BRIGHTNESS);
}

void loop() {
    delay(1000);
    statusLeds[STATUS_LED_ID_MAIN] = CHSV(0, 255, 255);
    FastLED.show(STATUS_LED_BRIGHTNESS);
    delay(1000);
    statusLeds[STATUS_LED_ID_MAIN] = CHSV(128, 255, 255);
    FastLED.show(STATUS_LED_BRIGHTNESS);
}