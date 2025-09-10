#include "animation/Abstract.h"
#include "stdexcept"

#include <FastLED.h>

void AbstractAnimation::step() {
    throw std::runtime_error("Not implemented");
}
