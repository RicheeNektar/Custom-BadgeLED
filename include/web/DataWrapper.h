#ifndef DATAWRAPPER_H
#define DATAWRAPPER_H

#include <Stream.h>

struct DataWrapper : virtual Stream {
    const uint8_t* data;
    const size_t len;

    size_t position = 0;

    DataWrapper(
        const uint8_t* data,
        const size_t len
    ):
        data(data),
        len(len)
    {}

    ~DataWrapper() override = default;

    size_t readBytes(char* buffer, size_t length) override;

    int peek() override;

    int available() override;

    int read() override;

    size_t write(uint8_t) override;
};

#endif //DATAWRAPPER_H
