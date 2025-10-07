#ifndef ANIMATION_CONFIG_H
#define ANIMATION_CONFIG_H

#include "AbstractConfig.h"

struct AnimationConfig final : virtual AbstractConfig {
    uint8_t mode;
    uint8_t brightness;
    uint8_t noiseLevel;
    uint16_t animationSpeed;
    uint16_t micFrequency;
    uint8_t primaryHue;
    uint8_t secondaryHue;

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

    const char* getContextName() override {
        return "animation";
    }

    void serialize(Print& file) const override;

    void deserialize(Stream& file) override;

    bool validate() override;

    void defaults() override;

    void nextMode();
};

extern AnimationConfig animationConfig;

#endif //ANIMATION_CONFIG_H
