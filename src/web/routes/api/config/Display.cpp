#include "Display.h"
#include "web/routes/api/config/Display.h"
#include "web/DataWrapper.h"
#include "config/Display.h"

#include <LittleFS.h>
#include <libb64/cdecode.h>

void ApiConfigDisplay::init(AsyncWebServer& server) {
    server.on("/api/config/display", HTTP_GET, get);
    server.on("/api/config/display", HTTP_POST, nullptr, nullptr, postBody);
    server.on("/api/config/display/image", HTTP_PUT, nullptr, putBitmap);
    server.on("/api/config/display/image", HTTP_DELETE, deleteBitmap);
}

void ApiConfigDisplay::get(AsyncWebServerRequest* request) {
    // Auto encodes to base64 for some reason
    AsyncResponseStream* stream = request->beginResponseStream("application/octet-stream");
    displayConfig.serialize(*stream);
    request->send(stream);
}

void ApiConfigDisplay::post(AsyncWebServerRequest* request) {
}

void ApiConfigDisplay::postBody(AsyncWebServerRequest* request, const uint8_t* data, const size_t len, size_t index, size_t total) {
    const size_t outLen = base64_decode_expected_len(len);
    char out[outLen];

    base64_decode_chars(reinterpret_cast<const char*>(data), len, out);

    DataWrapper wrapper(reinterpret_cast<const uint8_t*>(out), outLen);

    displayConfig.deserialize(wrapper);

    if (displayConfig.validate()) {
        request->send(204);
    } else {
        displayConfig.defaults();
        request->send(400, "text/plain", "Invalid config");
    }
}



void ApiConfigDisplay::deleteBitmap(AsyncWebServerRequest* request) {
    LittleFS.remove("/config/display.bmp");
    request->send(204);
}

void ApiConfigDisplay::putBitmap(AsyncWebServerRequest* request, const String& filename, size_t index, const uint8_t* data, const size_t len, bool final) {
    if (data[0] != 'B' && data[1] != 'M' && len < 512) {
        request->send(400, "text/plain", "Invalid BMP file");
        return;
    }

    const int sizeX = data[18] << 24 | data[19] << 16 | data[20] << 8 | data[21];
    const int sizeY = data[22] << 24 | data[23] << 16 | data[24] << 8 | data[25];

    if (sizeX != sizeY) {
        request->send(400, "text/plain", "Image must be square");
        return;
    }

    if (sizeX > DISPLAY_HEIGHT) {
        request->send(400, "text/plain", "Image is too large (max 128x128)");
        return;
    }

    File file = LittleFS.open("/config/display.bmp", FILE_WRITE, true);
    file.write(data, len);
    file.flush();
    file.close();

    request->send(204);
}

