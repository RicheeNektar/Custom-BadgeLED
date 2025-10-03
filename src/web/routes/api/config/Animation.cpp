#include "web/routes/api/config/Animation.h"
#include "config/Animation.h"

#include <libb64/cdecode.h>

#include "web/DataWrapper.h"

void ApiConfigAnimation::init(AsyncWebServer& server) {
    server.on("/api/config/animation", HTTP_GET, get);
    server.on("/api/config/animation", HTTP_POST, post);
    server.on("/api/config/animation", HTTP_PATCH, post, nullptr, patchBody);
}

void ApiConfigAnimation::get(AsyncWebServerRequest* request) {
    // Auto encodes to base64 for some reason
    AsyncResponseStream* stream = request->beginResponseStream("application/octet-stream");
    animationConfig.serialize(*stream);
    request->send(stream);
}

void ApiConfigAnimation::post(AsyncWebServerRequest* request) {
    animationConfig.save();
    request->send(204);
}

void ApiConfigAnimation::patchBody(AsyncWebServerRequest* request, const uint8_t* data, const size_t len, size_t index, size_t total) {
    const size_t outLen = base64_decode_expected_len(len);
    char out[outLen];

    base64_decode_chars(reinterpret_cast<const char*>(data), len, out);

    DataWrapper wrapper(reinterpret_cast<const uint8_t*>(out), outLen);

    animationConfig.deserialize(wrapper);

    if (animationConfig.validate()) {
        request->send(204);
    } else {
        animationConfig.defaults();
        request->send(400, "text/plain", "Invalid config");
    }
}
