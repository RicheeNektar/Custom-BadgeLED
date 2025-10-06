#ifndef OTA_H
#define OTA_H

#include <ESPAsyncWebServer.h>

struct OTA {
    static void init(AsyncWebServer& server);

    static void post(AsyncWebServerRequest* request);

    static void postFile(AsyncWebServerRequest* request, const String& filename, size_t index, const uint8_t* data, size_t len, bool final);
};



#endif //OTA_H
