#include "task/LEDAnimationTask.h"
#include "animation/Abstract.h"
#include "LEDS.h"

void LEDAnimationTask::init() {
    animationConfig.load();
    AbstractAnimation::reload();
}

void LEDAnimationTask::run() {
    auto* anim = animation.load();

    if (animation != nullptr) {
        anim->iterate();
        anim->step();
        ledControllers[LED_CTRL_MAIN]->showLeds(animationConfig.getBrightness());
    }

    vTaskDelay(animationConfig.getDelay() / portTICK_PERIOD_MS);
}

TaskHandle_t AnimationTaskHandle;

LEDAnimationTask animationTask;
