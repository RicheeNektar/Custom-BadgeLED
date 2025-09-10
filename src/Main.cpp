#include "Main.h"

#include <LittleFS.h>

void setup() {
    if (!LittleFS.begin()) {
        Serial.println("FS init failed");
    }
}

void loop() {
    delay(100);
}