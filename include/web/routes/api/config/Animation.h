#ifndef API_CONFIG_ANIMATION_H
#define API_CONFIG_ANIMATION_H

#include <ESPAsyncWebServer.h>

struct ApiConfigAnimation {
    static void init(AsyncWebServer& server);

    static void get(AsyncWebServerRequest* request);

    static void post(AsyncWebServerRequest* request);

    static void patchBody(AsyncWebServerRequest* request, const uint8_t* data, const size_t len, size_t index, size_t total);
};

#endif //API_CONFIG_ANIMATION_H
