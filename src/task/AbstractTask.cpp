#include "task/AbstractTask.h"

[[noreturn]] void TaskRun(void* param) {
    auto* task = static_cast<AbstractTask*>(param);

    task->init();

    do {
        task->run();

        vTaskDelay(50 / portTICK_PERIOD_MS);
    } while (true);
}

