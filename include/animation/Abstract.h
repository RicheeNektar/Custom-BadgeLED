#ifndef ABSTRACT_ANIMATION_H
#define ABSTRACT_ANIMATION_H

#include "config/Animation.h"
#include "Lock.h"

struct AbstractAnimation {
    virtual ~AbstractAnimation() = default;

    virtual void step() = 0;

    static void reload();

protected:
    static uint8_t offset();
};

extern Lock animationLock;

extern AbstractAnimation* animation;

#endif //ABSTRACT_ANIMATION_H