#include "Generics.h"
#include "Globals.h"
#include "web/routes/api/Generics.h"

#include <LittleFS.h>

void ApiGenerics::init(AsyncWebServer& server)
{
    server.on("/logs", HTTP_GET, getLogs);
    server.on("/version", HTTP_GET, getLogs);
}

void ApiGenerics::getLogs(AsyncWebServerRequest* request)
{
    request->beginResponse(LittleFS, LOG_FILE_PATH, "text/plain");
}

void ApiGenerics::getVersion(AsyncWebServerRequest* request)
{
    request->send(200, "text/plain", VERSION);
}
