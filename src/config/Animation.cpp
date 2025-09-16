#include "config/Animation.h"

AnimationConfig* AnimationConfig::standard() {
    return new AnimationConfig(
        0,
        0,
        128,
        100,
        50,
        0,
        180
    );
}

AnimationConfig* AnimationConfig::deserialize(File& file) {
    uint8_t mbuffer[2];

    file.read(mbuffer, sizeof(mbuffer));
    const uint16_t animationSpeed = mbuffer[0] | mbuffer[1] << 8;

    file.read(mbuffer, sizeof(mbuffer));
    const uint16_t micFrequency = mbuffer[0] | mbuffer[1] << 8;

    uint8_t brightness;
    uint8_t mode;
    uint8_t noiseLevel;
    uint8_t primaryHue;
    uint8_t secondaryHue;

    file.read(&brightness, 1);
    file.read(&mode, 1);
    file.read(&noiseLevel, 1);
    file.read(&primaryHue, 1);
    file.read(&secondaryHue, 1);

    return new AnimationConfig(
        mode,
        brightness,
        noiseLevel,
        animationSpeed,
        micFrequency,
        primaryHue,
        secondaryHue
    );
}

void AnimationConfig::serialize(File& file) const {
    const uint8_t buffer[] {
        static_cast<uint8_t>(this->animationSpeed & 0xFF),
        static_cast<uint8_t>(this->animationSpeed >> 8 & 0xFF),
        static_cast<uint8_t>(this->micFrequency & 0xFF),
        static_cast<uint8_t>(this->micFrequency >> 8 & 0xFF),
        this->brightness,
        this->mode,
        this->noiseLevel,
        this->primaryHue,
        this->secondaryHue
    };
    file.write(buffer, sizeof(buffer));
}
