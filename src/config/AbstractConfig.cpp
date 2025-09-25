#include "config/AbstractConfig.h"
#include "Globals.h"
#include "Logs.h"

#include <LittleFS.h>

#include "LEDS.h"

void AbstractConfig::load() {
    const char* name = getContextName();
    const String path = "/config/" + String(name);

    if (LittleFS.exists(path)) {
        File file = LittleFS.open(path, FILE_READ);
        deserialize(file);
        file.close();
    } else {
        defaults();
        save();
    }
}

void AbstractConfig::save() {
    const char* name = getContextName();
    File file;

    try {
        file = LittleFS.open("/config/" + String(name), FILE_WRITE, true);
        serialize(file);
        file.flush();
    } catch (std::exception& e) {
        log_e("%s", e.what());
    }

    file.close();
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
    if (text == nullptr) {
        constexpr uint8_t length = 0;
        file.write(&length, 1);
        return;
    }

    const uint8_t length = strlen(text);
    file.write(&length, 1);
    file.write(reinterpret_cast<const uint8_t*>(text), length);
}
