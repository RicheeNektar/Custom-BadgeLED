#ifndef DISPLAY_CONFIG_H
#define DISPLAY_CONFIG_H

#include "AbstractConfig.h"

struct DisplayConfig final : virtual AbstractConfig {
    uint8_t layout;
    uint8_t imageSizeX;
    uint8_t imageSizeY;
    uint8_t imageLen;
    const char* name;
    const char* telegram;
    const char* line1;
    const char* line2;
    const char* line3;
    uint8_t* image;

    DisplayConfig(
        const uint8_t layout,
        const uint8_t imageSizeX,
        const uint8_t imageSizeY,
        const uint8_t imageLen,
        const char* name,
        const char* telegram,
        const char* line1,
        const char* line2,
        const char* line3,
        uint8_t* image
    ):
        layout(layout),
        imageSizeX(imageSizeX),
        imageSizeY(imageSizeY),
        imageLen(imageLen),
        name(name),
        telegram(telegram),
        line1(line1),
        line2(line2),
        line3(line3),
        image(image)
    {}

    ~DisplayConfig() override {
        delete[] name;
        delete[] telegram;
        delete[] line1;
        delete[] line2;
        delete[] line3;
        delete[] image;
    };

    const char* getContextName() override {
        return "display";
    }

    void serialize(File& file) const override;

    void deserialize(File& file) override;

    void defaults() override;
};

extern DisplayConfig displayConfig;

#endif //DISPLAY_CONFIG_H
