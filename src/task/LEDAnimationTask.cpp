#include "task/LEDAnimationTask.h"
#include "animation/Abstract.h"
#include "LEDS.h"

void LEDAnimationTask::init() {
    animationConfig.load();
}

void LEDAnimationTask::run() {
    animationLock.waitForLock();

    if (animation != nullptr) {
        animation->step();
        FastLED[0].showLeds(animationConfig.brightness);
    }

    animationLock.unlock();
    vTaskDelay(animationConfig.animationSpeed);
}

TaskHandle_t AnimationTaskHandle;

LEDAnimationTask animationTask;
