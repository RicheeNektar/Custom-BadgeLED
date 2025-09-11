#include "animation/StaticColor.h"

void StaticColorAnimation::step() {
    for (auto i = 0; i < ledCount; i++) {
        leds[i] = CHSV(this->config->primaryHue, 255, 255);
    }
}
