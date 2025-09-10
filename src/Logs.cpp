#include "Logs.h"

#include <LittleFS.h>

void Logs::rotate(const String& channel) {
    const auto oldFileName = ("/logs/" + channel + ".old.log").c_str();
    LittleFS.remove(oldFileName);
    LittleFS.rename(("/logs/" + channel + ".log").c_str(), oldFileName);
}

void Logs::addf(const String& channel, const char* format, ...) {
    add(format, channel);
}

void Logs::add(const String& message) {
    add(message, LOG_CHANNEL_DEFAULT);
}

void Logs::add(const String& message, const String& channel) {
    const String fileName = "logs/" + channel + ".log";
    File f = LittleFS.open(fileName, "a", true);

    if (LOG_FILE_SIZE_LIMIT >= f.size()) {
        f.close();
        rotate(channel);
        f = LittleFS.open(fileName, "a", true);
    }

    const String entry = "[" + String(micros() / 1000) + "s] " + message;
    f.write(
        reinterpret_cast<const uint8_t *>(entry.c_str()),
        entry.length()
    );
    f.close();
}
