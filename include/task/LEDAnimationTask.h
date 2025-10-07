#ifndef ANIMATION_TASK_H
#define ANIMATION_TASK_H

#include "AbstractTask.h"

struct LEDAnimationTask final : virtual AbstractTask {
    void init() override;

    void run() override;
};

extern TaskHandle_t AnimationTaskHandle;

extern LEDAnimationTask animationTask;

#endif //ANIMATION_TASK_H
