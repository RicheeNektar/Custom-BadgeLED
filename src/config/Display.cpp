#include "config/Display.h"

DisplayConfig displayConfig{
    1,
    0,
    0,
    0,
    "Name",
    "Telegram",
    "Some text",
    "uwu~",
    "",
    nullptr,
};

void DisplayConfig::defaults() {
    this->layout = 1;
    this->imageSizeX = 0;
    this->imageSizeY = 0;
    this->imageLen = 0;
    this->name = "Name";
    this->telegram = "Telegram";
    this->line1 = "Some text";
    this->line2 = "uwu~";
    this->line3 = "";
    this->image = nullptr;
}

void DisplayConfig::deserialize(File& file) {
    file.read(&this->layout, 1);
    file.read(&this->imageSizeX, 1);
    file.read(&this->imageSizeY, 1);

    this->name = readString(file);
    this->telegram = readString(file);
    this->line1 = readString(file);
    this->line2 = readString(file);
    this->line3 = readString(file);

    file.read(&this->imageLen, 1);

    this->image = nullptr;
    if (imageLen > 0) {
        delete[] this->image;
        this->image = new uint8_t[imageLen];
        file.read(image, imageLen);
    }
}

void DisplayConfig::serialize(File& file) const {
    file.write(layout);
    file.write(imageSizeX);
    file.write(imageSizeY);

    writeString(file, name);
    writeString(file, telegram);
    writeString(file, line1);
    writeString(file, line2);
    writeString(file, line3);

    file.write(imageLen);
    file.write(image, imageLen);
}
