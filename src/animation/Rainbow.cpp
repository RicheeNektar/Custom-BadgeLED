#include "animation/Rainbow.h"

#include <fl/fill.h>

#include "LEDS.h"

void RainbowAnimation::step() {
    AbstractAnimation::step();
    fl::fill_rainbow(mainLeds, ledCount, micros() / 36000);
}
