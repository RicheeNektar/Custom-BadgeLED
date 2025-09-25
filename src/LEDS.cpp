#include "Globals.h"
#include "LEDS.h"

#include <FastLED.h>

void LEDS::init() {
    FastLED.addLeds<LED_TYPE, MAIN_LED_PIN, COLOR_ORDER>(mainLeds, NUM_MAIN_LEDS);
    FastLED.addLeds<LED_TYPE, STATUS_LED_PIN, COLOR_ORDER>(statusLeds, NUM_STATUS_LEDS);
}

void LEDS::error(const uint8_t code, const CRGB moduleColor) {
    statusLeds[0] = moduleColor;

    for (uint8_t i = 1; i < NUM_STATUS_LEDS; i++) {
        statusLeds[i] = (code >> (i - 1) & 1) > 0 ? STATUS_WHITE : STATUS_OFF;
    }
}

void LEDS::status(const uint8_t ledID, const CRGB color) {
    statusLeds[ledID] = color;
}

CRGB mainLeds[NUM_MAIN_LEDS];
CRGB statusLeds[NUM_STATUS_LEDS];
