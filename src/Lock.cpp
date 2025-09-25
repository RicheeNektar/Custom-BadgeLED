#include "Lock.h"

#include "task/AbstractTask.h"

void Lock::waitForLock() {
    while (!mutex.try_lock()) {
        vTaskDelay(pdMS_TO_TICKS(rand() * 50));
    }
}

void Lock::unlock() {
    mutex.unlock();
}


