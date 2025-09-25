#ifndef ABSTRACT_LAYOUT_H
#define ABSTRACT_LAYOUT_H

#include "model/Position.h"

#include <cstdint>

struct AbstractLayout {
    static AbstractLayout create(uint8_t id);

    virtual ~AbstractLayout() = default;

    virtual Position getNamePos() const;

    virtual Position getTelegramPos() const;

    virtual Position getLinesPos() const;

    virtual Position getImagePos() const;
};

#endif //ABSTRACT_LAYOUT_H
