#ifndef RAINBOW_H
#define RAINBOW_H

#include "Abstract.h"

struct RainbowAnimation final : virtual AbstractAnimation {
    using AbstractAnimation::AbstractAnimation;
    void step() override;
};


#endif //RAINBOW_H