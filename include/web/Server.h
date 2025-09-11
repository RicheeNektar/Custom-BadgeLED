#ifndef SERVER_H
#define SERVER_H

#include <ESPAsyncWebServer.h>

struct WebServer {
    static void registerRoutes();
};

extern AsyncWebServer _server;

#endif //SERVER_H
