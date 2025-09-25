#ifndef BUTTON_H
#define BUTTON_H

#include <crgb.h>
#include <FreeRTOS.h> // required for task.h
#include <task.h>

enum ButtonLongPressMode {
    NONE,
    ONCE,
    CONTINUOUS
};

class Button {
    uint64_t pressed = 0x0;
    uint64_t debounce = 0x0;

    void onPress();

    void onRelease();

    void setLED(CRGB crgb) const;

protected:
    ButtonLongPressMode longPressMode = NONE;
    uint8_t statusLED = 0;
    uint8_t buttonPin = 0;

    virtual void onShortPress() = 0;

    virtual void onLongPress() = 0;

public:
    virtual ~Button() = default;

    void check();
};

#endif //BUTTON_H
