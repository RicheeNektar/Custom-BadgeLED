#ifndef MODE_BUTTON_H
#define MODE_BUTTON_H

#include "Globals.h"
#include "button/AbstractButton.h"

class ModeButton final : public virtual Button {
protected:
    void onLongPress() override;

    void onShortPress() override;

public:
    ModeButton() {
        buttonPin = MODE_BUTTON_PIN;
        statusLED = STATUS_LED_ID_MODE;
        longPressMode = ONCE;
    }
};

#endif //MODE_BUTTON_H
