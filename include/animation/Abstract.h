#ifndef ABSTRACT_ANIMATION_H
#define ABSTRACT_ANIMATION_H

#include "../config/Animation.h"

#include <FastLED.h>

struct AbstractAnimation {
    explicit AbstractAnimation(CRGB* leds, AnimationConfig* config): leds(leds), config(config) {}

    virtual ~AbstractAnimation() = default;

    virtual void step();

protected:
    AnimationConfig* config;
    CRGB* leds;
};


#endif //ABSTRACT_ANIMATION_H