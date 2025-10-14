#include "LEDS.h"
#include "Firmware.h"
#include "web/routes/OTA.h"

#include <Update.h>
#include <LittleFS.h>

void OTA::init(AsyncWebServer& server) {
    server.on("/ota/update", HTTP_POST, post, postFile);
    server.on("/ota/update", HTTP_GET, get);
}

void OTA::get(AsyncWebServerRequest* request) {
    switch (UPDATE_STATUS)
    {
        case UPDATE_STATUS_SUCCESS:
            request->send(200);
            return;
        case UPDATE_STATUS_IDLE:
            request->send(400);
            return;
        case UPDATE_STATUS_UPLOADING:
        case UPDATE_STATUS_IN_PROGRESS:
            request->send(204);
            return;
        case UPDATE_STATUS_ERROR:
            switch (UPDATE_RESULT)
            {
                case UPDATE_RESULT_MISSING_FIRMWARE:
                    request->send(400, "text/plain", "Missing firmware");
                    return;
                case UPDATE_RESULT_INVALID_VERSION:
                    request->send(400, "text/plain", "Invalid version");
                    return;
                case UPDATE_RESULT_OUTDATED_VERSION:
                    request->send(400, "text/plain", "Outdated version");
                    return;
                case UPDATE_RESULT_FILE_PATH_TOO_LONG:
                    request->send(400, "text/plain", "Invalid firmware");
                    return;
                default:
                    break;
            }
        default:
            request->send(500, "text/plain", "Unmapped update status!");
    }
}

void OTA::post(AsyncWebServerRequest* request) {
    if (UPDATE_STATUS != UPDATE_STATUS_UPLOADING)
    {
        // Update idle or already in progress!
        request->send(400);
        return;
    }

    xTaskCreatePinnedToCore(
        [](void*)
        {
            UPDATE_STATUS = UPDATE_STATUS_IN_PROGRESS;
            Firmware::update();

            vTaskDelay(pdMS_TO_TICKS(5000));

            if (UPDATE_RESULT == UPDATE_RESULT_SUCCESS)
            {
                ESP.restart();
            }
            else
            {
                UPDATE_STATUS = UPDATE_STATUS_IDLE;
                UPDATE_RESULT = UPDATE_RESULT_NONE;
            }

            vTaskDelete(nullptr);
        },
        "FirmwareUpdate",
        4096,
        nullptr,
        0xFF,
        nullptr,
        1
    );
    request->send(201);
}

void OTA::postFile(AsyncWebServerRequest* request, const String& filename, size_t index, const uint8_t* data, const size_t len, bool final) {
    if (UPDATE_STATUS == UPDATE_STATUS_IDLE)
    {
        UPDATE_STATUS = UPDATE_STATUS_UPLOADING;

        if (LittleFS.exists(TEMP_FIRMWARE_PATH))
        {
            LittleFS.remove(TEMP_FIRMWARE_PATH);
        }
    }

    File file = LittleFS.open(TEMP_FIRMWARE_PATH, FILE_APPEND);
    file.write(data, len);
    file.flush();
    file.close();
}
