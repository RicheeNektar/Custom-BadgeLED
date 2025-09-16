#ifndef LEDS_H
#define LEDS_H

#include "Globals.h"
#include "animation/Abstract.h"

#include <crgb.h>

struct LEDS {
    static void init();
    static void mainStatusLoop();

    static void error(uint8_t code, CRGB moduleColor);
};

extern AbstractAnimation* animation;

extern CRGB mainLeds[NUM_MAIN_LEDS];
extern CRGB statusLeds[NUM_STATUS_LEDS];

#endif //LEDS_H
