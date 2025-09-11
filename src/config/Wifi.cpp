#include "config/Wifi.h"

void WifiConfig::serialize(const File &file) const {

}

WifiConfig* WifiConfig::deserialize(const File &file) {
    return new WifiConfig(
        true,
        "Test",
        "Demo"
    );
}
