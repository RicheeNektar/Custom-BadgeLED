#ifndef ABSTRACT_TASK_H
#define ABSTRACT_TASK_H

#include <FreeRTOS.h> // required for task.h
#include <task.h>

void TaskRun(void*);

struct AbstractTask {
    virtual void init() = 0;
    virtual void run() = 0;

    virtual ~AbstractTask() = default;
};

#endif //ABSTRACT_TASK_H
