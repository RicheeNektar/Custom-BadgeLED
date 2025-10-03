#ifndef DISPLAY_H
#define DISPLAY_H

#include "config/Display.h"

#include <GxEPD2_3C.h>

#define ENABLE_GxEPD2_GFX 1

#define MAX_DISPLAY_BUFFER_SIZE 800
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))

#define DISPLAY_WIDTH 296
#define DISPLAY_HEIGHT 128

using DISPLAY_TYPE = GxEPD2_3C<GxEPD2_290_C90c, GxEPD2_290_C90c::HEIGHT>;
extern DISPLAY_TYPE displayApi;

struct Display {
    static void redraw();
};

#endif //DISPLAY_H
