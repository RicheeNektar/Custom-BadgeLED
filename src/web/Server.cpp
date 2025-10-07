#include "web/Server.h"
#include "web/routes/api/config/Animation.h"
#include "web/routes/api/config/Display.h"
#include "web/routes/api/config/Network.h"

#include <LittleFS.h>

void WebServer::init() {
    ApiConfigAnimation::init(_server);
    ApiConfigDisplay::init(_server);
    ApiConfigNetwork::init(_server);

    // Static web content
    _server.serveStatic("/config", LittleFS, "/config");
    _server.serveStatic("/logs", LittleFS, "/logs");

    _server.serveStatic("/", LittleFS, "/web");

    _server.onNotFound([](AsyncWebServerRequest* request) {
        request->send(LittleFS, "/web/404.htm", "text/html");
    });
}

void WebServer::start() {
    _server.begin();
}

void WebServer::stop() {
    _server.end();
}

AsyncWebServer _server(80);
