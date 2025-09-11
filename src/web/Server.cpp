#include "web/Server.h"
#include "web/routes/Animations.h"

#include <LittleFS.h>
#include <ElegantOTA.h>

void WebServer::init() {
    // Static web content
    webServer.serveStatic("/", LittleFS, "/web");

    // Controllers
    webServer.on(
        "/",
        HTTP_POST,
        PatchAnimations::handle
    );

    // OTA Handler
    ElegantOTA.begin(&webServer, "", "");

    webServer.begin();
}

AsyncWebServer webServer(443);
