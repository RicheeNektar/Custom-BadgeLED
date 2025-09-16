#include "Logs.h"
#include "LEDS.h"

#include <LittleFS.h>

void Logs::rotate() {
    const String oldFileName = "/logs/old.log";
    LittleFS.remove(oldFileName);
    LittleFS.rename("/logs/latest.log", oldFileName);
}

void Logs::addf(const char* format, ...) {
    va_list argv;
    va_start(argv, format);
    vprintf(format, argv);
    va_end(argv);
    add(format);
}

void Logs::add(const String message) {
    Serial.println(message);

    const String fileName = "/logs/latest.log";
    File f = LittleFS.open(fileName, FILE_APPEND, true);

    if (f.size() >= LOG_FILE_SIZE_LIMIT) {
        f.close();
        rotate();
        f = LittleFS.open(fileName, FILE_APPEND, true);
    }

    const String entry = "[" + String(micros() / 1000) + "ms] " + message + "\r\n";
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
    add(format);
    LEDS::error(code, moduleColor);
}

void Logs::error(const String message, const uint8_t code, const CRGB moduleColor) {
    add(message);
    LEDS::error(code, moduleColor);
}
