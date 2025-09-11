#include "LEDS.h"
#include "Globals.h"

#include <FastLED.h>

#include "animation/StaticColor.h"
#include "config/Animation.h"

void LEDS::init() {
    FastLED.addLeds<LED_TYPE, MAIN_LED_PIN, COLOR_ORDER>(mainLeds, NUM_MAIN_LEDS);
    FastLED.addLeds<LED_TYPE, STATUS_LED_PIN, COLOR_ORDER>(statusLeds, NUM_STATUS_LEDS);
}

void LEDS::mainStatusLoop() {
    const auto config = AnimationConfig::load();

    animation = new StaticColorAnimation(mainLeds, NUM_MAIN_LEDS, config);
    animation->step();

    FastLED[0].showLeds(config->brightness);
}

LEDS LEDs;

AbstractAnimation* animation = nullptr;

CRGB mainLeds[NUM_MAIN_LEDS];
CRGB statusLeds[NUM_STATUS_LEDS];
