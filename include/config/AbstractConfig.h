#ifndef ABSTRACT_CONFIG_H
#define ABSTRACT_CONFIG_H

#include <FS.h>

#include "Logs.h"

class AbstractConfig {
protected:
    static char* readString(File& file);

    static void writeString(File& file, const char* text);

    virtual const char* getContextName() = 0;

    virtual void serialize(File& file) const = 0;

    virtual void deserialize(File& file) = 0;

public:
    virtual ~AbstractConfig() = default;

    void save();

    void load();

    virtual void defaults() = 0;
};

#endif //ABSTRACT_CONFIG_H
