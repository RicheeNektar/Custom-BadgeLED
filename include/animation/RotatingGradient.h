#ifndef ROTATING_GRADIENT_H
#define ROTATING_GRADIENT_H

#include "Abstract.h"

struct RotatingGradient final : virtual AbstractAnimation {
    void step() override;
};


#endif //ROTATING_GRADIENT_H