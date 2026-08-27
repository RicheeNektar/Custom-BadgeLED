#ifndef ANIMATION_CONFIG_H
#define ANIMATION_CONFIG_H

#include "AbstractConfig.h"

#define DEFAULT_MODE 0
#define DEFAULT_BRIGHTNESS 10
#define DEFAULT_NOISE_LEVEL 128
#define DEFAULT_DELAY 100
#define DEFAULT_MIC_FREQUENCY 50
#define DEFAULT_PRIMARY_HUE 0
#define DEFAULT_SECONDARY_HUE 60

#define MIN_MODE static_cast<uint8_t>(0)
#define MIN_BRIGHTNESS static_cast<uint8_t>(0)
#define MIN_NOISE_LEVEL static_cast<uint8_t>(0)
#define MIN_ANIMATION_DELAY static_cast<uint16_t>(10)
#define MIN_MIC_FREQUENCY static_cast<uint16_t>(1)
#define MIN_PRIMARY_HUE static_cast<uint8_t>(0)
#define MIN_SECONDARY_HUE static_cast<uint8_t>(0)

#define MAX_MODE static_cast<uint8_t>(2)
#define MAX_BRIGHTNESS static_cast<uint8_t>(10)
#define MAX_NOISE_LEVEL static_cast<uint8_t>(255)
#define MAX_DELAY static_cast<uint16_t>(1000)
#define MAX_MIC_FREQUENCY static_cast<uint16_t>(255)
#define MAX_PRIMARY_HUE static_cast<uint8_t>(255)
#define MAX_SECONDARY_HUE static_cast<uint8_t>(255)

struct AnimationConfig final : virtual AbstractConfig {
private:
    uint8_t _mode;
    uint8_t _brightness;
    uint8_t _noiseLevel;
    uint16_t _delay;
    uint16_t _micFrequency;
    uint8_t _primaryHue;
    uint8_t _secondaryHue;

protected:
    const char* getContextName() override {
        return "animation";
    }

public:
    void serialize(Print& file) const override;

    void deserialize(Stream& file) override;

    explicit AnimationConfig(
        const uint8_t mode = DEFAULT_MODE,
        const uint8_t brightness = DEFAULT_BRIGHTNESS,
        const uint8_t noiseLevel = DEFAULT_NOISE_LEVEL,
        const uint16_t delay = DEFAULT_DELAY,
        const uint16_t micFrequency = DEFAULT_MIC_FREQUENCY,
        const uint8_t primaryHue = DEFAULT_PRIMARY_HUE,
        const uint8_t secondaryHue = DEFAULT_SECONDARY_HUE
    ):
        _mode(mode),
        _brightness(brightness),
        _noiseLevel(noiseLevel),
        _delay(delay),
        _micFrequency(micFrequency),
        _primaryHue(primaryHue),
        _secondaryHue(secondaryHue)
    {}

    bool validate() override;

    void defaults() override;

    void setMode(const uint8_t mode)
    {
        _mode = mode % 2;
    }
    void setBrightness(const uint8_t brightness)
    {
        _brightness = std::max(std::min(brightness, MAX_BRIGHTNESS), MIN_BRIGHTNESS);
    }
    void setNoiseLevel(const uint8_t noiseLevel)
    {
        _noiseLevel = std::max(std::min(noiseLevel, MAX_NOISE_LEVEL), MIN_NOISE_LEVEL);
    }
    void setDelay(const uint16_t delay)
    {
        _delay = std::max(std::min(delay, MAX_DELAY), MIN_ANIMATION_DELAY);
    }
    void setMicFrequency(const uint16_t micFrequency)
    {
        _micFrequency = std::max(std::min(micFrequency, MAX_MIC_FREQUENCY), MIN_MIC_FREQUENCY);
    }
    void setPrimaryHue(const uint8_t primaryHue)
    {
        _primaryHue = std::max(std::min(primaryHue, MAX_PRIMARY_HUE), MIN_PRIMARY_HUE);
    }
    void setSecondaryHue(const uint8_t secondaryHue)
    {
        _secondaryHue = std::max(std::min(secondaryHue, MAX_SECONDARY_HUE), MIN_SECONDARY_HUE);
    }

    uint8_t getMode() const
    {
        return _mode;
    }
    uint8_t getBrightness() const
    {
        return _brightness;
    }
    uint8_t getNoiseLevel() const
    {
        return _noiseLevel;
    }
    uint16_t getDelay() const
    {
        return _delay;
    }
    uint16_t getMicFrequency() const
    {
        return _micFrequency;
    }
    uint8_t getPrimaryHue() const
    {
        return _primaryHue;
    }
    uint8_t getSecondaryHue() const
    {
        return _secondaryHue;
    }
};

extern AnimationConfig animationConfig;

#endif //ANIMATION_CONFIG_H
