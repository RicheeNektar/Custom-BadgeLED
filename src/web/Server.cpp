#include "web/Server.h"
#include "web/routes/Animations.h"

#include <LittleFS.h>
#include <ElegantOTA.h>

void WebServer::registerRoutes() {
    // Static web content
    _server.serveStatic("/", LittleFS, "/web");

    // OTA Handler
    ElegantOTA.begin(&_server, "", "");

    _server.begin();
}

AsyncWebServer _server(80);
