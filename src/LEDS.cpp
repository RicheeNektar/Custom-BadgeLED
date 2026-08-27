#include "Globals.h"
#include "LEDS.h"

#include <FastLED.h>

void LEDS::init() {
    ledControllers[LED_CTRL_MAIN] = & CFastLED::addLeds<LED_TYPE, MAIN_LED_PIN, COLOR_ORDER>(mainLeds, NUM_MAIN_LEDS);
    ledControllers[LED_CTRL_STATUS] = & CFastLED::addLeds<LED_TYPE, STATUS_LED_PIN, COLOR_ORDER>(statusLeds, NUM_STATUS_LEDS);
}

void LEDS::error(const uint8_t code, const CRGB moduleColor) {
    ledMutex.lock();

    statusLeds[STATUS_LED_ID_MAIN] = moduleColor;

    for (uint8_t i = 1; i < NUM_STATUS_LEDS; i++) {
        statusLeds[i] = (code >> (i - 1) & 1) > 0 ? STATUS_WHITE : STATUS_OFF;
    }

    ledControllers[LED_CTRL_STATUS]->showLeds(STATUS_LED_BRIGHTNESS);
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    ledMutex.unlock();
}

void LEDS::status(const uint8_t ledID, const CRGB color) {
    ledMutex.lock();

    statusLeds[ledID] = color;
    ledControllers[LED_CTRL_STATUS]->showLeds(STATUS_LED_BRIGHTNESS);

    ledMutex.unlock();
}

std::mutex ledMutex;

CRGB mainLeds[NUM_MAIN_LEDS];
CRGB statusLeds[NUM_STATUS_LEDS];
CLEDController* ledControllers[NUM_LED_CONTROLLERS];
