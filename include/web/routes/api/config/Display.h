#ifndef API_CONFIG_DISPLAY_H
#define API_CONFIG_DISPLAY_H

#include <ESPAsyncWebServer.h>

struct ApiConfigDisplay {
    static void init(AsyncWebServer& server);

    static void get(AsyncWebServerRequest* request);

    static void post(AsyncWebServerRequest* request);

    static void postBody(AsyncWebServerRequest* request, const uint8_t* data, size_t len, size_t index, size_t total);

    static void deleteBitmap(AsyncWebServerRequest* request);

    static void putBitmap(AsyncWebServerRequest* request, const String& filename, size_t index, const uint8_t* data, size_t len, bool final);
};

#endif //API_CONFIG_DISPLAY_H
