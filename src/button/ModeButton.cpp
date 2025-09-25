#include "button/ModeButton.h"

#include "animation/Abstract.h"
#include "config/Wifi.h"
#include "wifi/AccessPoint.h"

void ModeButton::onLongPress() {
    log_d("Toggle AP");

    wifiConfig.enabled = !wifiConfig.enabled;

    AccessPoint::restart();
}

void ModeButton::onShortPress() {
    log_d("Mode short");

    animationConfig.nextMode();

    AbstractAnimation::reload();
}
