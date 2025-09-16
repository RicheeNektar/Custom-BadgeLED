#include "web/Server.h"
#include "web/routes/PatchAnimations.h"

#include <LittleFS.h>
#include <ElegantOTA.h>

void WebServer::init() {
    // Static web content
    _server.serveStatic("/config", LittleFS, "/config");
    _server.serveStatic("/logs", LittleFS, "/logs");

    _server.serveStatic("/", LittleFS, "/web");

    _server.onNotFound([](AsyncWebServerRequest* request) {
        request->send(LittleFS, "/web/404.htm", "text/html");
    });

    _server.on("/", HTTP_PATCH, PatchAnimations::handle);

    // OTA Handler
    ElegantOTA.begin(&_server, "", "");

    _server.begin();
}

AsyncWebServer _server(80);
