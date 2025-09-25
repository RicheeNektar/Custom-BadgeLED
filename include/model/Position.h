#ifndef POSITION_H
#define POSITION_H

#include <cstdint>

struct Position final {
    const uint8_t x;
    const uint8_t y;

    Position(const uint8_t x, const uint8_t y): x(x), y(y) {}
};

#endif //POSITION_H
