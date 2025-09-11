#ifndef LEDS_H
#define LEDS_H

#include <crgb.h>

#include "Globals.h"

struct LEDS {
    static void init();
    static void mainStatusLoop();
};

extern LEDS* Leds;

extern CRGB mainLeds[NUM_MAIN_LEDS];
extern CRGB statusLeds[NUM_STATUS_LEDS];

#endif //LEDS_H
