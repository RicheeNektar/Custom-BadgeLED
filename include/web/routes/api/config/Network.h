#ifndef API_CONFIG_NETWORK_H
#define API_CONFIG_NETWORK_H

#include <ESPAsyncWebServer.h>

struct ApiConfigNetwork {
    static void init(AsyncWebServer& server);

    static void get(AsyncWebServerRequest* request);

    static void post(AsyncWebServerRequest* request);

    static void postBody(AsyncWebServerRequest* request, const uint8_t* data, size_t len, size_t index, size_t total);
};

#endif //API_CONFIG_NETWORK_H
