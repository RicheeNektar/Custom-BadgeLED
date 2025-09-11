#include "config/Abstract.h"
#include "config/Wifi.h"
#include "config/Animation.h"

#include <LittleFS.h>

template<typename T>
T* AbstractConfig<T>::load() {
    const String name = T::getContextName();
    File file = LittleFS.open("/config/" + name + ".json", FILE_READ);

    try {
        T* obj = T::deserialize(file);
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
        this->serialize(file);
    } catch (...) {
    }
    file.close();
}

template WifiConfig* AbstractConfig<WifiConfig>::load();
template void AbstractConfig<WifiConfig>::save();

template AnimationConfig* AbstractConfig<AnimationConfig>::load();
template void AbstractConfig<AnimationConfig>::save();
