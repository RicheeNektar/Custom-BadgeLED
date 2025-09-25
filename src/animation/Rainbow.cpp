#include "animation/Rainbow.h"
#include "LEDS.h"

#include <fl/fill.h>

void RainbowAnimation::step() {
    fill_rainbow(mainLeds, NUM_MAIN_LEDS, offset());
}
