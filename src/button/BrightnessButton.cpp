#include "button/BrightnessButton.h"
#include "config/Animation.h"

static void updateBrightness()
{
    animationConfig.setBrightness(animationConfig.getBrightness() + 1);
}

void BrightnessButton::onLongPress() {
    updateBrightness();
}

void BrightnessButton::onShortPress() {
    updateBrightness();
}
