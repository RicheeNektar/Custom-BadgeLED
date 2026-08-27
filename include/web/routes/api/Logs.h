#ifndef API_LOGS_H
#define API_LOGS_H

#include <ESPAsyncWebServer.h>

struct ApiLogs
{
    static void init(AsyncWebServer& server);

    static void get(AsyncWebServerRequest* request);
};

#endif //API_LOGS_H
