#ifndef LEDS_H
#define LEDS_H

#include "Globals.h"

#include <crgb.h>
#include <FastLED.h>

struct LEDS {
    static void init();

    static void error(uint8_t code, CRGB moduleColor);

    static void status(uint8_t ledID, CRGB color);
};

extern CRGB mainLeds[NUM_MAIN_LEDS];
extern CRGB statusLeds[NUM_STATUS_LEDS];

#endif //LEDS_H
