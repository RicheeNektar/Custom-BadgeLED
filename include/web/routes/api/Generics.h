#ifndef API_GENERICS_H
#define API_GENERICS_H

#include <ESPAsyncWebServer.h>

struct ApiGenerics
{
    static void init(AsyncWebServer& server);

    static void getLogs(AsyncWebServerRequest* request);

    static void getVersion(AsyncWebServerRequest* request);
};

#endif //API_GENERICS_H
