#ifndef SERVER_H
#define SERVER_H

#include <ESPAsyncWebServer.h>

struct WebServer {
    static void init();

    static void start();

    static void stop();
};

extern AsyncWebServer _server;

#endif //SERVER_H
