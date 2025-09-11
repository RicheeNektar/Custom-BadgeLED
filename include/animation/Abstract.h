#ifndef ABSTRACT_ANIMATION_H
#define ABSTRACT_ANIMATION_H

#include "config/Animation.h"

#include <crgb.h>

struct AbstractAnimation {
    explicit AbstractAnimation(CRGB* leds, const int ledCount, const AnimationConfig* config): config(config), ledCount(ledCount), leds(leds) {}

    virtual ~AbstractAnimation() = default;

    virtual void step();

protected:
    const AnimationConfig* config;
    const int ledCount;
    CRGB* leds;
};


#endif //ABSTRACT_ANIMATION_H