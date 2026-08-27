#ifndef ABSTRACT_ANIMATION_H
#define ABSTRACT_ANIMATION_H

#include "config/Animation.h"

#include <atomic>

struct AbstractAnimation {
private:
    int _iterations = 0;

public:
    virtual ~AbstractAnimation() = default;

    void iterate();

    static void reload();

    virtual void step() = 0;

    int offset() const;
};

extern std::atomic<AbstractAnimation*> animation;

#endif //ABSTRACT_ANIMATION_H