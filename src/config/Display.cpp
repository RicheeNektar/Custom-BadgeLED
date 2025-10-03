#include "config/Display.h"

DisplayConfig displayConfig{
    1,
    "Name",
    "Telegram",
    "Some text",
    "uwu~",
    ""
};

void DisplayConfig::defaults() {
    this->layout = 1;
    this->name = "Name";
    this->telegram = "Telegram";
    this->line1 = "Some text";
    this->line2 = "uwu~";
    this->line3 = "";
}

void DisplayConfig::deserialize(Stream& file) {
    file.readBytes(&this->layout, 1);

    this->name = readString(file);
    this->telegram = readString(file);
    this->line1 = readString(file);
    this->line2 = readString(file);
    this->line3 = readString(file);
}

void DisplayConfig::serialize(Print& file) const {
    file.write(layout);

    writeString(file, name);
    writeString(file, telegram);
    writeString(file, line1);
    writeString(file, line2);
    writeString(file, line3);
}

bool DisplayConfig::validate() {
    return true;
}
