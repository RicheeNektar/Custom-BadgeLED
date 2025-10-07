#include "config/Display.h"

DisplayConfig displayConfig{
    1,
    true,
    false,
    "Name",
    "Telegram",
    "Some text",
    "uwu~",
    ""
};

void DisplayConfig::defaults() {
    this->layout = 1;
    this->nameColorRed = true;
    this->invertedColors = false;
    this->name = "Name";
    this->telegram = "Telegram";
    this->line1 = "Some text";
    this->line2 = "uwu~";
    this->line3 = "";
}

void DisplayConfig::deserialize(Stream& file) {
    file.readBytes(&this->layout, 1);

    file.readBytes(reinterpret_cast<uint8_t*>(&this->nameColorRed), 1);
    file.readBytes(reinterpret_cast<uint8_t*>(&this->invertedColors), 1);

    this->name = readString(file);
    this->telegram = readString(file);
    this->line1 = readString(file);
    this->line2 = readString(file);
    this->line3 = readString(file);
}

void DisplayConfig::serialize(Print& file) const {
    file.write(layout);

    file.write(this->nameColorRed);
    file.write(this->invertedColors);

    writeString(file, name);
    writeString(file, telegram);
    writeString(file, line1);
    writeString(file, line2);
    writeString(file, line3);
}

bool DisplayConfig::validate() {
    return true;
}
