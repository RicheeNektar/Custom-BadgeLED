#include "animation/RotatingGradient.h"
#include "Globals.h"
#include "LEDS.h"

CRGB lerp(const CRGB a, const CRGB b, const float t) {
    return CRGB(
        t * (b.r - a.r) + a.r,
        t * (b.g - a.g) + a.g,
        t * (b.b - a.b) + a.b
    );
}

void RotatingGradient::step() {
    const uint8_t offset = micros() / (animationConfig.animationSpeed * 1000) % NUM_MAIN_LEDS;

    CRGB primary;
    hsv2rgb_raw(CHSV(animationConfig.primaryHue, 255, 255), primary);

    CRGB secondary;
    hsv2rgb_raw(CHSV(animationConfig.secondaryHue, 255, 255), secondary);


    for (uint8_t i = 0; i < NUM_MAIN_LEDS; i++) {
        mainLeds[(i + offset) % NUM_MAIN_LEDS] = lerp(
            primary,
            secondary,
            static_cast<float>(i) / NUM_MAIN_LEDS
        );
    }
}
