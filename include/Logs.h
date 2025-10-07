#ifndef LOGS_H
#define LOGS_H

#include <crgb.h>
#include <WString.h>

#define LOG_FILE_SIZE_LIMIT 1024 // 1 KiB

struct Logs {
    static void rotate();

    static void add(const String& message);

    static void addf(const char* format, ...) __attribute__ ((format (printf, 1, 2)));

    static void errorf(uint8_t code, CRGB moduleColor, const char* format, ...) __attribute__ ((format (printf, 3, 4)));

    static void error(const String& message, uint8_t code, CRGB moduleColor);
};

#endif //LOGS_H
