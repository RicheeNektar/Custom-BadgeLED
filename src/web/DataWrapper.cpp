#include "web/DataWrapper.h"

#include <algorithm>
#include <esp32-hal-log.h>

size_t DataWrapper::readBytes(char* buffer, const size_t length) {
    if (stream != nullptr) {
        return stream->readBytes(buffer, length);
    }

    const size_t dataSize = std::min(length, len - position);

    if (dataSize <= 0) {
        return 0;
    }

    memcpy(buffer, data + position, dataSize);

    position += dataSize;

    return dataSize;
}

int DataWrapper::available() {
    if (stream != nullptr) {
        return stream->available();
    }

    return static_cast<signed>(len - position);
}

int DataWrapper::peek() {
    if (stream != nullptr) {
        return stream->peek();
    }

    return data[position];
}

int DataWrapper::read() {
    if (stream != nullptr) {
        return stream->read();
    }

    return data[position++];
}

size_t DataWrapper::write(uint8_t) {
    return 0;
}

uint32_t DataWrapper::readUInt32() {
    return static_cast<unsigned>(read()) << 24
         | static_cast<unsigned>(read()) << 16
         | static_cast<unsigned>(read()) << 8
         | static_cast<unsigned>(read());
}
