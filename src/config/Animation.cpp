#include "config/Animation.h"

AnimationConfig animationConfig{
    0,
    10,
    128,
    180,
    50,
    0,
    180,
};

void AnimationConfig::defaults() {
    this->mode = 0;
    this->brightness = 10;
    this->noiseLevel = 128;
    this->animationSpeed = 100;
    this->micFrequency = 50;
    this->primaryHue = 0;
    this->secondaryHue = 60;
}

void AnimationConfig::nextMode() {
    mode = (mode + 1) % 2;
}

void AnimationConfig::deserialize(File& file) {
    uint8_t mbuffer[2];

    file.read(mbuffer, sizeof(mbuffer));
    this->animationSpeed = mbuffer[0] | mbuffer[1] << 8;

    file.read(mbuffer, sizeof(mbuffer));
    this->micFrequency = mbuffer[0] | mbuffer[1] << 8;

    file.read(&this->brightness, 1);
    file.read(&this->mode, 1);
    file.read(&this->noiseLevel, 1);
    file.read(&this->primaryHue, 1);
    file.read(&this->secondaryHue, 1);
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
