#include "config/Abstract.h"

#include <LittleFS.h>

template<class T>
T* AbstractConfig<T>::load() {
    const String name = T::getContextName();
    File file = LittleFS.open("/config/" + name + ".json", FILE_READ);

    try {
        T obj = T::deserialize(file);
        file.close();
        return obj;
    } catch (...) {
        file.close();
        return nullptr;
    }
}

template<class T>
void AbstractConfig<T>::save() {
    const String name = T::getContextName();
    File file = LittleFS.open("/config/" + name + ".json", FILE_READ);

    try {
        T obj = T::serialize(file);
    } catch (...) {
    }
    file.close();
}



