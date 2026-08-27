#include "task/ButtonTask.h"
#include "button/ModeButton.h"
#include "button/SAOButton.h"
#include "button/BrightnessButton.h"

void ButtonTask::init() {}

void ButtonTask::run() {
    for (int i = 0; i < NUM_BUTTONS; ++i) {
        Button* b = buttons[i];
        if (b != nullptr) {
            b->check();
        }
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
}

Button* buttons[NUM_BUTTONS] = {
    new ModeButton,
    new SaoButton,
    new BrightnessButton,
};

TaskHandle_t ButtonTaskHandle;

ButtonTask buttonTask;
