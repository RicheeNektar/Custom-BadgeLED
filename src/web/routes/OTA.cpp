#include "Globals.h"
#include "web/DataWrapper.h"
#include "web/routes/OTA.h"

#include <Update.h>
#include <LittleFS.h>

#include "LEDS.h"

#define TEMP_FIRMWARE_PATH "/firmware.tmp"

/*
 * Header
 *   4B Version (iVersion)
 *   4B Firmware length
 *
 * Web Files
 *   4B Files count
 *
 *   File header
 *     4B File path length (/index.htm -> 0x0B)
 *     4B File size
 *   File
 *     .. File path
 *     .. Data
 *
 * Firmware
 *   .. Data
 */

void OTA::init(AsyncWebServer& server) {
    server.on("/ota/update", HTTP_POST, post, postFile);
}

void OTA::cleanup(File firmwareFile) {
    firmwareFile.close();
    LittleFS.remove("/firmware.tmp");
}

void OTA::post(AsyncWebServerRequest* request) {
    File firmwareFile = LittleFS.open(TEMP_FIRMWARE_PATH, FILE_READ);

    if (!firmwareFile) {
        request->send(400, "text/plain", "Missing firmware");
        cleanup(firmwareFile);
        return;
    }

    DataWrapper wrapper(&firmwareFile);
    const uint32_t version = wrapper.readUInt32();

    if (
        // The first byte should be 0
        (version & 0xFF000000) != 0
    ) {
        request->send(403, "text/plain", "Invalid version");
        cleanup(firmwareFile);
        return;
    }

    if (
        version < iVERSION
    ) {
        request->send(403, "text/plain", "Outdated version");
        cleanup(firmwareFile);
        return;
    }

    const uint32_t firmwareLength = wrapper.readUInt32();
    const uint32_t filesCount = wrapper.readUInt32();

    log_e("%d", filesCount);

    for (uint32_t i = 0; i < filesCount; i++) {
        const uint32_t filepathLength = wrapper.readUInt32();
        const uint32_t fileSize = wrapper.readUInt32();

        char filePath[filepathLength + 1];
        wrapper.readBytes(filePath, filepathLength);
        filePath[filepathLength] = '\0';

        char buffer[fileSize];
        wrapper.readBytes(buffer, fileSize);

        File file = LittleFS.open("/web.new/" + String(filePath), FILE_WRITE, true);
        file.write(reinterpret_cast<const uint8_t*>(buffer), fileSize);
        file.flush();
        file.close();

        log_e("%d", i);
        log_print_buf(reinterpret_cast<const uint8_t*>(buffer), fileSize);
        log_e("%s", filePath);
    }

    log_e("%d - Done", wrapper.available());

    LEDS::status(STATUS_LED_ID_MAIN, STATUS_YELLOW);

    Update.begin(firmwareLength);
    Update.writeStream(wrapper);
    cleanup(firmwareFile);
    Update.end();

    request->send(204);
}

void OTA::postFile(AsyncWebServerRequest* request, const String& filename, size_t index, const uint8_t* data, const size_t len, bool final) {
    File file = LittleFS.open(TEMP_FIRMWARE_PATH, FILE_APPEND);
    file.write(data, len);
    file.flush();
    file.close();
}
