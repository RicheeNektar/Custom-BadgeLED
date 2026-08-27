#include "Globals.h"

#include "animation/Abstract.h"
#include "animation/Rainbow.h"
#include "animation/RotatingGradient.h"

void AbstractAnimation::iterate()
{
    _iterations = (_iterations + 1) % NUM_MAIN_LEDS;
}

int AbstractAnimation::offset() const
{
    return _iterations;
}

void AbstractAnimation::reload() {
    const auto* previous = animation.load();

    switch (animationConfig.getMode()) {
        case 0:
            animation.store(new RotatingGradient());
            break;
        case 1:
            animation.store(new RainbowAnimation());
            break;
        default:
            animation.store(new RotatingGradient());
            break;
    }

    delete previous;
}

std::atomic<AbstractAnimation*> animation(nullptr);
