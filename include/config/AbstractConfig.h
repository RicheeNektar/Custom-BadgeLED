#ifndef ABSTRACT_CONFIG_H
#define ABSTRACT_CONFIG_H

#include <FS.h>

class AbstractConfig {
protected:
    static char* readString(Stream& file);

    static void writeString(Print& file, const char* text);

    virtual const char* getContextName() = 0;

    virtual void serialize(Print& file) const = 0;

    virtual void deserialize(Stream& file) = 0;

    virtual bool validate() = 0;

public:
    virtual ~AbstractConfig() = default;

    void save();

    void load();

    virtual void defaults() = 0;
};

#endif //ABSTRACT_CONFIG_H
