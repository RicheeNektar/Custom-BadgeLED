#ifndef LOCK_H
#define LOCK_H

#include <mutex>

class Lock {
    std::mutex mutex;

public:
    Lock() = default;

    void waitForLock();
    void unlock();
};

#endif //LOCK_H
