#include "Globals.h"
#include "LEDS.h"
#include "animation/StaticColor.h"
#include "config/Animation.h"
#include "animation/Rainbow.h"

#include <FastLED.h>

void LEDS::init() {
    FastLED.addLeds<LED_TYPE, MAIN_LED_PIN, COLOR_ORDER>(mainLeds, NUM_MAIN_LEDS);
    FastLED.addLeds<LED_TYPE, STATUS_LED_PIN, COLOR_ORDER>(statusLeds, NUM_STATUS_LEDS);
}

void LEDS::mainStatusLoop() {
    if (animation == nullptr) {
        const AnimationConfig* config = AnimationConfig::load();
        animation = new RainbowAnimation(mainLeds, NUM_MAIN_LEDS, config);
    }
    animation->step();
    FastLED.show(STATUS_LED_BRIGHTNESS);
}

void LEDS::error(const uint8_t code, const CRGB moduleColor) {
    statusLeds[0] = moduleColor;
    for (uint8_t i = 1; i < NUM_STATUS_LEDS; i++) {
        statusLeds[i] = (code >> (i-1) & 1) > 0 ? STATUS_GREEN : STATUS_RED;
    }
}

AbstractAnimation* animation = nullptr;

CRGB mainLeds[NUM_MAIN_LEDS];
CRGB statusLeds[NUM_STATUS_LEDS];
