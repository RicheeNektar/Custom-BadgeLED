#ifndef ABSTRACT_CONFIG_H
#define ABSTRACT_CONFIG_H

#include <WString.h>
#include <ArduinoJson.h>
#include <FS.h>

template<class T>
struct AbstractConfig {
    virtual ~AbstractConfig() = default;

    static T* load();

    void save();

protected:
    static String getContextName() {
        throw std::runtime_error("Not implemented");
    }

    virtual void serialize(File& file) const {
        throw std::runtime_error("Not implemented");
    }

    static T* deserialize(File& file) {
        throw std::runtime_error("Not implemented");
    }

    static T* standard() {
        throw std::runtime_error("Not implemented");
    }
};

#endif //ABSTRACT_CONFIG_H
