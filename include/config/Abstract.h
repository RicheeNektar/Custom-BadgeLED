#ifndef ABSTRACT_CONFIG_H
#define ABSTRACT_CONFIG_H

#include <FS.h>
#include <WString.h>

template<class T>
struct AbstractConfig;

template<class T>
struct AbstractConfig {
    virtual ~AbstractConfig() = default;

    static T* load();

    void save();

protected:
    static String getContextName() {
        throw std::runtime_error("Not implemented");
    }

    virtual void serialize(const File& file) const {
        throw std::runtime_error("Not implemented");
    }

    virtual T& deserialize(const File& file) const {
        throw std::runtime_error("Not implemented");
    }
};

#endif //ABSTRACT_CONFIG_H
