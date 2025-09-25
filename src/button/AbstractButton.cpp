#include "button/AbstractButton.h"
#include "Globals.h"
#include "LEDS.h"

#include <esp32-hal-gpio.h>

void Button::check() {
    if (0 == buttonPin) {
        return;
    }

    const bool isPressed = HIGH == digitalRead(buttonPin);

    if (isPressed) {
        onPress();
    } else {
        onRelease();
    }
}

void Button::onPress() {
    if (0 == pressed) {
        pressed = micros();
    } else if (
        longPressMode != NONE
    ) {
        if (
            (
                0 == debounce
                && micros() - pressed > BUTTON_LONG_PRESS_DURATION_m
            )
            || (
                longPressMode == CONTINUOUS
                && micros() - debounce > BUTTON_LONG_PRESS_COOLDOWN_m
            )
        ) {
            log_d("Long press");
            setLED(STATUS_WHITE);

            debounce = micros();
            onLongPress();
        }
    }
}

void Button::onRelease() {
    if (pressed) {
        if (0 == debounce) {
            setLED(STATUS_WHITE);
            debounce = micros();
            onShortPress();
            log_d("Short press");
        } else if (
            micros() - debounce > BUTTON_COOLDOWN_m
        ) {
            setLED(STATUS_OFF);
            pressed = 0;
            debounce = 0;
        }
    }
}

void Button::setLED(const CRGB crgb) const {
    if (statusLED > 0) {
        LEDS::status(statusLED, crgb);
    }
}
