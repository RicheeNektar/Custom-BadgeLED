#ifndef BRIGHT_BUTTON_H
#define BRIGHT_BUTTON_H

#include "Globals.h"
#include "button/AbstractButton.h"

class BrightnessButton final : public virtual Button {
protected:
    void onLongPress() override;

    void onShortPress() override;

public:
    BrightnessButton() {
        buttonPin = BRIGHT_BUTTON_PIN;
        statusLED = STATUS_LED_ID_BRIGHTNESS;
        longPressMode = CONTINUOUS;
    }
};

#endif //BRIGHT_BUTTON_H
