#ifndef DISPLAY_CONFIG_H
#define DISPLAY_CONFIG_H

#include "AbstractConfig.h"

struct DisplayConfig final : virtual AbstractConfig {
    uint8_t layout;
    bool nameColorRed;
    bool invertedColors;
    const char* name;
    const char* telegram;
    const char* line1;
    const char* line2;
    const char* line3;

    DisplayConfig(
        const uint8_t layout,
        const bool nameColorRed,
        const bool invertedColors,
        const char* name,
        const char* telegram,
        const char* line1,
        const char* line2,
        const char* line3
    ):
        layout(layout),
        nameColorRed(nameColorRed),
        invertedColors(invertedColors),
        name(name),
        telegram(telegram),
        line1(line1),
        line2(line2),
        line3(line3)
    {}

    ~DisplayConfig() override {
        delete[] name;
        delete[] telegram;
        delete[] line1;
        delete[] line2;
        delete[] line3;
    };

    const char* getContextName() override {
        return "display";
    }

    void serialize(Print& file) const override;

    void deserialize(Stream& file) override;

    bool validate() override;

    void defaults() override;
};

extern DisplayConfig displayConfig;

#endif //DISPLAY_CONFIG_H
