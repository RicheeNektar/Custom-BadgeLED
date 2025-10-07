#ifndef BUTTON_TASK_H
#define BUTTON_TASK_H

#include "button/AbstractButton.h"
#include "task/AbstractTask.h"

struct ButtonTask : virtual AbstractTask {
    void init() override;

    void run() override;
};

extern Button* buttons[];

extern ButtonTask buttonTask;
extern TaskHandle_t ButtonTaskHandle;

#endif //BUTTON_TASK_H
