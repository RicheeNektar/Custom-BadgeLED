#include "button/SAOButton.h"

#include "config/Animation.h"
#include "config/Display.h"
#include "config/Wifi.h"

void SaoButton::onLongPress() {
}

void SaoButton::onShortPress() {
    wifiConfig.save();
    animationConfig.save();
    displayConfig.save();
}
