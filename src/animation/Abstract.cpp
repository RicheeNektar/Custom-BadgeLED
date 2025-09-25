#include "animation/Abstract.h"
#include "animation/Rainbow.h"
#include "animation/RotatingGradient.h"
#include "Globals.h"

uint8_t AbstractAnimation::offset() {
    return micros() / NUM_MAIN_LEDS / 1000;
}

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
