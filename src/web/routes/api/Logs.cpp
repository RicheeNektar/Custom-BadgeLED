#include "Logs.h"
#include "web/routes/api/Logs.h"

#include <LittleFS.h>

void ApiLogs::init(AsyncWebServer& server)
{
    server.on("/logs", HTTP_GET, get);
}

void ApiLogs::get(AsyncWebServerRequest* request)
{
    request->beginResponse(LittleFS, LOG_FILE_PATH, "text/plain");
}
