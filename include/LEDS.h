#ifndef LEDS_H
#define LEDS_H

#include <crgb.h>

#include "Globals.h"
#include "animation/Abstract.h"

struct LEDS {
    void init();
    void mainStatusLoop();
};

extern LEDS LEDs;
extern AbstractAnimation* animation;

extern CRGB mainLeds[NUM_MAIN_LEDS];
extern CRGB statusLeds[NUM_STATUS_LEDS];

#endif //LEDS_H
