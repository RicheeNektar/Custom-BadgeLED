#include "animation/Abstract.h"
#include "animation/Rainbow.h"
#include "animation/RotatingGradient.h"

void AbstractAnimation::reload() {
    animationLock.waitForLock();

    delete animation;

    switch (animationConfig.mode) {
        case 0:
            animation = new RotatingGradient();
            break;
        case 1:
            animation = new RainbowAnimation();
            break;
        default:
            animation = new RotatingGradient();
            break;
    }

    animationLock.unlock();
}

Lock animationLock{};

AbstractAnimation* animation = nullptr;
