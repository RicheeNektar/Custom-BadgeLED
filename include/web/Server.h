#ifndef SERVER_H
#define SERVER_H

#include <ESPAsyncWebServer.h>

struct WebServer {
    static void init();
};

extern AsyncWebServer* webServer;

#endif //SERVER_H
