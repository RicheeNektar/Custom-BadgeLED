#include "config/AbstractConfig.h"
#include "Globals.h"
#include "Logs.h"

#include <LittleFS.h>

#include "LEDS.h"

void AbstractConfig::load() {
    const char* name = this->getContextName();
    const String path = "/config/" + String(name);

    if (LittleFS.exists(path)) {
        File file = LittleFS.open(path, FILE_READ);
        this->deserialize(file);
        file.close();
    } else {
        this->defaults();
        // this->save();
    }
}

void AbstractConfig::save() {
    const char* name = this->getContextName();
    File file;

    LEDS::status(STATUS_LED_ID_MAIN, STATUS_YELLOW);
    try {
        file = LittleFS.open("/config/" + String(name), FILE_WRITE, true);
        this->serialize(file);
        file.flush();
    } catch (...) {
        Logs::errorf(ERROR_FS_WRITE, ERROR_MODULE_FS, "Failed to save config '%s'", name);
    }
    file.close();
    LEDS::status(STATUS_LED_ID_MAIN, STATUS_OFF);
}

char* AbstractConfig::readString(File& file) {
    uint8_t length;
    file.read(&length, 1);

    if (length == 0) {
        return nullptr;
    }

    uint8_t* text = new uint8_t[length + 1];
    file.read(text, length);
    text[length] = '\0';

    return reinterpret_cast<char*>(text);
}

void AbstractConfig::writeString(File& file, const char* text) {
    const uint8_t length = strlen(text);
    file.write(&length, 1);
    file.write(reinterpret_cast<const uint8_t*>(text), length);
}
