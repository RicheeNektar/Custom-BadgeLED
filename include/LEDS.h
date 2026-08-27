#ifndef LEDS_H
#define LEDS_H

#include "Globals.h"

#include <mutex>
#include <crgb.h>
#include <FastLED.h>

struct LEDS {
    static void init();

    static void error(uint8_t code, CRGB moduleColor);

    static void status(uint8_t ledID, CRGB color);
};

extern std::mutex ledMutex;

extern CRGB mainLeds[NUM_MAIN_LEDS];
extern CRGB statusLeds[NUM_STATUS_LEDS];

extern CLEDController* ledControllers[NUM_LED_CONTROLLERS];

#endif //LEDS_H
