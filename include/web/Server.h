#ifndef SERVER_H
#define SERVER_H

#include <ESPAsyncWebServer.h>

struct WebServer {
    static void init();
};

extern AsyncWebServer _server;

#endif //SERVER_H
