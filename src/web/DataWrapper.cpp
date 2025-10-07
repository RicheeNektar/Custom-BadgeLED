#include "web/DataWrapper.h"

#include <algorithm>
#include <esp32-hal-log.h>

size_t DataWrapper::readBytes(char* buffer, const size_t length) {
    const size_t dataSize = std::min(length, len - position);

    if (dataSize <= 0) {
        return 0;
    }

    memcpy(buffer, data + position, dataSize);

    position += dataSize;

    return dataSize;
}

int DataWrapper::available() {
    return len - position;
}

int DataWrapper::peek() {
    return data[position];
}

int DataWrapper::read() {
    return data[position++];
}

size_t DataWrapper::write(uint8_t) {
    return 0;
}

