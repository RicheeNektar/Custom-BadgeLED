#include "animation/RotatingGradient.h"
#include "Globals.h"
#include "LEDS.h"

void RotatingGradient::step() {
    CRGB primary;
    hsv2rgb_raw(CHSV(animationConfig.getPrimaryHue(), 255, 255), primary);

    CRGB secondary;
    hsv2rgb_raw(CHSV(animationConfig.getSecondaryHue(), 255, 255), secondary);

    for (auto i = 0; i < NUM_MAIN_LEDS; i++) {
        mainLeds[(i + offset()) % NUM_MAIN_LEDS] = CRGB::blend(
            primary,
            secondary,
            static_cast<fl::u8>(255 * (static_cast<float>(i) / 2 / NUM_MAIN_LEDS))
        );
    }
}
