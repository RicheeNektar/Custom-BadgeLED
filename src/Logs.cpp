#include "Logs.h"
#include "LEDS.h"

#include <LittleFS.h>

void Logs::rotate() {
    const String oldFileName = LOG_FILE_PATH_OLD;
    LittleFS.remove(oldFileName);
    LittleFS.rename(LOG_FILE_PATH, oldFileName);
}

void Logs::addf(const char* format, ...) {
    va_list argv;
    va_start(argv, format);
    vprintf(format, argv);
    va_end(argv);
    add(format);
}

void Logs::add(const String& message, const char type) {
    File f = LittleFS.open(LOG_FILE_PATH, FILE_APPEND, true);

    if (f.size() >= LOG_FILE_SIZE_LIMIT) {
        f.close();
        rotate();
        f = LittleFS.open(LOG_FILE_PATH, FILE_APPEND, true);
    }

    const String entry = "0x" + String(type) + "|[" + String(micros() / 1000) + "ms] " + message + "\r\n";
    f.write(
        reinterpret_cast<const uint8_t *>(entry.c_str()),
        entry.length()
    );
    f.close();
}

void Logs::errorf(const uint8_t code, const CRGB moduleColor, const char* format, ...) {
    va_list argv;
    va_start(argv, format);
    vprintf(format, argv);
    va_end(argv);
    add(format, 1);
    LEDS::error(code, moduleColor);
}

void Logs::error(const String& message, const uint8_t code, const CRGB moduleColor) {
    add(message, 1);
    LEDS::error(code, moduleColor);
}
