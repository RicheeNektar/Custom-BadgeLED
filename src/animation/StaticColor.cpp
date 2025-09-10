#include "animation/StaticColor.h"
#include "Globals.h"

void StaticColorAnimation::step() {
    for (auto i = 0; i < NUM_MAIN_LEDS; i++) {
        leds[i] = CHSV(this->config->primaryHue, 255, 255);
    }
}
