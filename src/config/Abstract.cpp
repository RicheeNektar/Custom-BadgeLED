#include "config/Abstract.h"
#include "config/Wifi.h"
#include "config/Animation.h"
#include "Globals.h"
#include "Logs.h"

#include <LittleFS.h>
#include <ArduinoJson.h>

template<typename T>
T* AbstractConfig<T>::load() {
    const String name = T::getContextName();

    File file;
    T* config = nullptr;

    try {
        const String path = "/config/" + name;
        file = LittleFS.open(path, FILE_READ);
        if (false == file) {
            config = T::standard();
            config->save();
        } else {
            config = T::deserialize(file);
        }
    } catch (std::exception& e) {
        Logs::errorf(ERROR_FS_LOAD, ERROR_MODULE_FS, "Failed to read config '%s': %s", name.c_str(), e.what());
    }
    file.close();
    return config;
}

template<typename T>
void AbstractConfig<T>::save() {
    const String name = T::getContextName();
    File file;

    try {
        file = LittleFS.open("/config/" + name, FILE_WRITE, true);
        this->serialize(file);
        file.flush();
    } catch (std::exception& e) {
        Logs::errorf(ERROR_FS_LOAD, ERROR_MODULE_FS, "Failed to read config '%s': %s", name.c_str(), e.what());
    }
    file.close();
}

template WifiConfig* AbstractConfig<WifiConfig>::load();
template void AbstractConfig<WifiConfig>::save();

template AnimationConfig* AbstractConfig<AnimationConfig>::load();
template void AbstractConfig<AnimationConfig>::save();
