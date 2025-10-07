#include "Display.h"
#include "display/AbstractLayout.h"

void Display::redraw() {
    AbstractLayout layout = AbstractLayout::create(displayConfig.layout);

    displayApi.clearScreen();
}
