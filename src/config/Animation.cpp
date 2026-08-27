#include "config/Animation.h"

AnimationConfig animationConfig;

void AnimationConfig::defaults() {
    setMode(DEFAULT_MODE);
    setBrightness(DEFAULT_BRIGHTNESS);
    setNoiseLevel(DEFAULT_NOISE_LEVEL);
    setDelay(DEFAULT_DELAY);
    setMicFrequency(DEFAULT_MIC_FREQUENCY);
    setPrimaryHue(DEFAULT_PRIMARY_HUE);
    setSecondaryHue(DEFAULT_SECONDARY_HUE);
}

void AnimationConfig::deserialize(Stream& file) {
    uint8_t mbuffer[2];

    file.readBytes(mbuffer, sizeof(mbuffer));
    setDelay(mbuffer[0] | mbuffer[1] << 8);

    file.readBytes(mbuffer, sizeof(mbuffer));
    setMicFrequency(mbuffer[0] | mbuffer[1] << 8);

    setBrightness(file.read());
    setMode(file.read());
    setNoiseLevel(file.read());
    setPrimaryHue(file.read());
    setSecondaryHue(file.read());
}

void AnimationConfig::serialize(Print& file) const {
    const uint8_t buffer[] {
        static_cast<uint8_t>(_delay & 0xFF),
        static_cast<uint8_t>(_delay >> 8 & 0xFF),
        static_cast<uint8_t>(_micFrequency & 0xFF),
        static_cast<uint8_t>(_micFrequency >> 8 & 0xFF),
        _brightness,
        _mode,
        _noiseLevel,
        _primaryHue,
        _secondaryHue
    };
    file.write(buffer, sizeof(buffer));
}

bool AnimationConfig::validate() {
    return true;
}
