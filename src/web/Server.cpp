#include "web/Server.h"

#include <LittleFS.h>

void WebServer::init() {
    webServer = new AsyncWebServer(443);
    webServer->serveStatic("/", LittleFS, "/web");
    webServer->on("/", HTTP_PATCH, );
}

AsyncWebServer* webServer;
