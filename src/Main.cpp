#include "Main.h"
#include "Globals.h"
#include "BQ25895.h"
#include "LEDS.h"
#include "Logs.h"
#include "web/Server.h"
#include "wifi/AccessPoint.h"
#include "task/LEDAnimationTask.h"
#include "task/ButtonTask.h"

#include <Arduino.h>
#include <LittleFS.h>

#include "Firmware.h"

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

void setup() {
    setupPins();

    LEDS::init();

    if (!LittleFS.begin()) {
        LEDS::error(ERROR_FS_INIT, ERROR_MODULE_FS);
        return;
    }

    Logs::add("--[[ REBOOT ]]--");

    Firmware::init();
    WebServer::init();

    if (!AccessPoint::init()) {
        Logs::error("AP failed", ERROR_AP_INIT, ERROR_MODULE_AP);
    }

    BQ25895::init();
}

void loop() {
    xTaskCreatePinnedToCore(
        TaskRun,
        "LEDAnimationTask",
        8192,
        &animationTask,
        1,
        &AnimationTaskHandle,
        1
    );

    TaskRun(&buttonTask);
}