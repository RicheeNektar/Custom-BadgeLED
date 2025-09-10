#ifndef STATIC_COLOR_H
#define STATIC_COLOR_H

#include "Abstract.h"

struct StaticColorAnimation final : virtual AbstractAnimation {
    using AbstractAnimation::AbstractAnimation;
    void step() override;
};


#endif //STATIC_COLOR_H