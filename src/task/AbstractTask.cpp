#include "task/AbstractTask.h"

[[noreturn]] void TaskRun(void* param) {
    AbstractTask* task = static_cast<AbstractTask*>(param);

    task->init();

    do {
        task->run();

        vTaskDelay(pdMS_TO_TICKS(50));
    } while (true);
}

