#include "Main.h"
#include "Globals.h"
#include "BQ25895.h"
#include "LEDS.h"
#include "Logs.h"
#include "web/Server.h"
#include "wifi/AccessPoint.h"
#include "task/LEDAnimationTask.h"
#include "task/ButtonTask.h"
#include "config/Wifi.h"

#include <Arduino.h>
#include <LittleFS.h>

void setupPins() {
    pinMode(BOOT_BUTTON_PIN, INPUT_PULLUP);

    pinMode(MODE_BUTTON_PIN, INPUT_PULLDOWN);
    pinMode(COLOR_BUTTON_PIN, INPUT_PULLDOWN);
    pinMode(BRIGHT_BUTTON_PIN, INPUT_PULLDOWN);
    pinMode(SAO_BUTTON_PIN, INPUT_PULLDOWN);

    pinMode(STATUS_LED_PIN, OUTPUT);
    digitalWrite(STATUS_LED_PIN, LOW);

    pinMode(MAIN_LED_PIN, OUTPUT);
    digitalWrite(MAIN_LED_PIN, LOW);

    pinMode(LIGHT_EN, OUTPUT);
    digitalWrite(LIGHT_EN, HIGH);
}

void setupTasks() {
    xTaskCreatePinnedToCore(
        TaskRun,
        "ButtonTask",
        8192,
        &buttonTask,
        2,
        &ButtonTaskHandle,
        1
    );

    xTaskCreatePinnedToCore(
        TaskRun,
        "LEDAnimationTask",
        8192,
        &animationTask,
        1,
        &AnimationTaskHandle,
        1
    );
}

void setup() {
    setupPins();

    LEDS::init();

    if (!LittleFS.begin()) {
        LEDS::error(ERROR_FS_INIT, ERROR_MODULE_FS);
        return;
    }

    Logs::add("--[[ REBOOT ]]--");

    WebServer::init();

    if (!AccessPoint::init()) {
        Logs::error("AP failed", ERROR_AP_INIT, ERROR_MODULE_AP);
    }

    BQ25895::init();

    setupTasks();
}

void loop() {
    LEDS::status(STATUS_LED_ID_MAIN, wifiConfig.enabled ? STATUS_GREEN : STATUS_RED);
    FastLED[1].showLeds(STATUS_LED_BRIGHTNESS);

    vTaskDelay(pdMS_TO_TICKS(50));
}