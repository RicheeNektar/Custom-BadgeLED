#include "animation/Rainbow.h"
#include "LEDS.h"

#include <fl/fill.h>

void RainbowAnimation::step() {
    const uint8_t offset = micros() / (animationConfig.animationSpeed * 1000);
    fill_rainbow(mainLeds, NUM_MAIN_LEDS, offset);
}
