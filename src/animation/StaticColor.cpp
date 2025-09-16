#include "animation/StaticColor.h"

void StaticColorAnimation::step() {
    AbstractAnimation::step();

    for (int i = 0; i < ledCount; i++) {
        leds[i] = CHSV(
            this->config->primaryHue + static_cast<float>(i) / ledCount * (this->config->secondaryHue - this->config->primaryHue),
            255,
            255
        );
    }
}
