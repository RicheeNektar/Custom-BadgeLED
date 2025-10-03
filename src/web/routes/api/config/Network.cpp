#include "web/routes/api/config/Network.h"
#include "web/DataWrapper.h"
#include "web/Server.h"
#include "config/Wifi.h"
#include "wifi/AccessPoint.h"

#include <libb64/cdecode.h>

void ApiConfigNetwork::init(AsyncWebServer& server) {
    server.on("/api/config/network", HTTP_GET, get);
    server.on("/api/config/network", HTTP_POST, post, nullptr, postBody);
}

void ApiConfigNetwork::get(AsyncWebServerRequest* request) {
    // Auto encodes to base64 for some reason
    AsyncResponseStream* stream = request->beginResponseStream("application/octet-stream");
    wifiConfig.serialize(*stream);
    request->send(stream);
}

void ApiConfigNetwork::post(AsyncWebServerRequest* request) {
}

void ApiConfigNetwork::postBody(AsyncWebServerRequest* request, const uint8_t* data, const size_t len, size_t index, size_t total) {
    const size_t outLen = base64_decode_expected_len(len);
    char out[outLen];

    base64_decode_chars(reinterpret_cast<const char*>(data), len, out);

    DataWrapper wrapper(reinterpret_cast<const uint8_t*>(out), outLen);

    wifiConfig.deserialize(wrapper);

    if (wifiConfig.validate()) {
        wifiConfig.save();

        request->send(204);

        vTaskDelay(pdMS_TO_TICKS(1000));

        AccessPoint::restart();
    } else {
        wifiConfig.defaults();
        request->send(400, "text/plain", "Invalid config");
    }
}
