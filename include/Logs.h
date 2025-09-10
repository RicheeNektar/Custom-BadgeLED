#ifndef LOGS_H
#define LOGS_H

#include <WString.h>

#define LOG_FILE_SIZE_LIMIT 1024 // 1 KiB

#define LOG_CHANNEL_CHARGER "charger"
#define LOG_CHANNEL_DEFAULT "default"

struct Logs {
    static void rotate(const String& channel);

    static void add(const String& message, const String& channel);

    static void add(const String& message);

    static void addf(const String& channel, const char* format, ...) __attribute__ ((format (printf, 2, 3)));
};

#endif //LOGS_H
