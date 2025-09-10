#ifndef ANIMATION_CONFIG_H
#define ANIMATION_CONFIG_H

#include "Abstract.h"

struct AnimationConfig final : virtual AbstractConfig<AnimationConfig> {
    const uint8_t mode;
    const uint8_t brightness;
    const uint8_t noiseLevel;
    const uint16_t animationSpeed;
    const uint16_t micFrequency;
    const uint8_t primaryHue;
    const uint8_t secondaryHue;

    AnimationConfig(
        const uint8_t mode,
        const uint8_t brightness,
        const uint8_t noiseLevel,
        const uint16_t animationSpeed,
        const uint16_t micFrequency,
        const uint8_t primaryHue,
        const uint8_t secondaryHue
    ):
        mode(mode),
        brightness(brightness),
        noiseLevel(noiseLevel),
        animationSpeed(animationSpeed),
        micFrequency(micFrequency),
        primaryHue(primaryHue),
        secondaryHue(secondaryHue)
    {}

    static String getContextName() {
        return String("animation");
    }

    void serialize(const File& file) const override;
};

#endif //ANIMATION_CONFIG_H
