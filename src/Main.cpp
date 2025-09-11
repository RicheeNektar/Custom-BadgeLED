#include "Main.h"

#include <FastLED.h>
#include <LittleFS.h>

#include "Globals.h"
#include "web/Server.h"
#include "wifi/AP.h"

void setup() {
    Serial.begin(115200);
    Serial.print("Pins init..");

    pinMode(STATUS_LED_PIN, OUTPUT);
    pinMode(BOOT_BUTTON_PIN, INPUT_PULLUP);

    pinMode(MODE_BUTTON, INPUT);
    pinMode(COLOR_BUTTON, INPUT);
    pinMode(BRIGHT_BUTTON, INPUT);
    pinMode(SAO_BUTTON, INPUT);

    pinMode(LIGHT_EN, OUTPUT);

    digitalWrite(STATUS_LED_PIN, LOW);
    digitalWrite(LIGHT_EN, HIGH);

    Serial.println("OK!");

    Serial.print("FS init..");
    if (!LittleFS.begin()) {
        Serial.println("ERR");
        return;
    }
    Serial.println("OK!");

    Serial.print("AP init..");
    AP::init();
    Serial.println("OK!");

    Serial.print("Server init..");
    WebServer::init();
    Serial.println("OK!");
}

void loop() {}