#ifndef DATAWRAPPER_H
#define DATAWRAPPER_H

#include <Stream.h>

struct DataWrapper final : virtual Stream {
    const uint8_t* data;
    const size_t len;
    Stream* stream;

    size_t position = 0;

    explicit DataWrapper(
        Stream* stream
    ):
        data(nullptr),
        len(0),
        stream(stream)
    {}

    explicit DataWrapper(
        const uint8_t* data,
        const size_t len
    ):
        data(data),
        len(len),
        stream(nullptr)
    {}

    ~DataWrapper() override = default;

    size_t readBytes(char* buffer, size_t length) override;

    int peek() override;

    int available() override;

    int read() override;

    size_t write(uint8_t) override;

    uint32_t readUInt32();

    void skip(int bytes);
};

#endif //DATAWRAPPER_H
