#ifndef SAO_BUTTON_H
#define SAO_BUTTON_H

#include "Globals.h"
#include "button/AbstractButton.h"

class SaoButton final : public virtual Button {
protected:
    void onLongPress() override;

    void onShortPress() override;

public:
    SaoButton() {
        buttonPin = SAO_BUTTON_PIN;
        statusLED = STATUS_LED_ID_SAO;
        longPressMode = ONCE;
    }
};

#endif //SAO_BUTTON_H
