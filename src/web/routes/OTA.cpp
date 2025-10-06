#include "Globals.h"
#include "web/DataWrapper.h"
#include "web/routes/OTA.h"

#include <Update.h>
#include <LittleFS.h>

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
    server.on("/ota/update", HTTP_PUT, post, postFile);
}

void OTA::post(AsyncWebServerRequest* request) {
}

void OTA::postFile(AsyncWebServerRequest* request, const String& filename, size_t index, const uint8_t* data, const size_t len, bool final) {
    if (len < 1024) {
        request->send(403, "text/plain", "Invalid firmware file");
        return;
    }

    DataWrapper wrapper(data, len);
    const uint32_t version = wrapper.readUInt32();

    if (version < iVERSION) {
        request->send(403, "text/plain", "Outdated version");
        return;
    }

    const uint32_t firmwareLength = wrapper.readUInt32();
    const uint32_t filesCount = wrapper.readUInt32();

    for (uint32_t i = 0; i < filesCount; i++) {
        const uint32_t filepathLength = wrapper.readUInt32();
        const uint32_t fileSize = wrapper.readUInt32();

        char fileName[filepathLength];
        wrapper.readBytes(fileName, filepathLength);

        char fileData[fileSize];
        wrapper.readBytes(fileData, fileSize);

        File file = LittleFS.open("/web.new" + String(fileName), FILE_WRITE, true);
        file.write(reinterpret_cast<const uint8_t*>(fileData), fileSize);
        file.flush();
        file.close();
    }

    Update.begin(firmwareLength);
    Update.writeStream(wrapper);
    Update.end();

    request->send(204);
}
