#include "button/ModeButton.h"
#include "animation/Abstract.h"
#include "config/Wifi.h"
#include "wifi/AccessPoint.h"

void ModeButton::onLongPress() {
    wifiConfig.enabled = !wifiConfig.enabled;

    AccessPoint::restart();
}

void ModeButton::onShortPress() {
    animationConfig.nextMode();

    AbstractAnimation::reload();
}
