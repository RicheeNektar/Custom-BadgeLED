#include "display/AbstractLayout.h"
#include "display/DefaultLayout.h"
#include "Logs.h"

#include <stdexcept>

AbstractLayout AbstractLayout::create(const uint8_t id) {
    switch (id) {
        case 0:
            return static_cast<AbstractLayout>(DefaultLayout{});
        default:
            throw new std::runtime_error("Unknown layout");
    }
}

Position AbstractLayout::getNamePos() const {
    return Position{0,0};
}

Position AbstractLayout::getTelegramPos() const {
    return Position{0,0};
}

Position AbstractLayout::getLinesPos() const {
    return Position{0,0};
}

Position AbstractLayout::getImagePos() const {
    return Position{0,0};
}
