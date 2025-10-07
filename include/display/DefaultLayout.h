#ifndef DEFAULT_LAYOUT_H
#define DEFAULT_LAYOUT_H

#include "AbstractLayout.h"

struct DefaultLayout final : virtual AbstractLayout {
    Position getNamePos() const override;

    Position getTelegramPos() const override;

    Position getLinesPos() const override;

    Position getImagePos() const override;
};

#endif //DEFAULT_LAYOUT_H
