#ifndef GLOBALS_H
#define GLOBALS_H

#define VERSION "0.0.0"

#define MAIN_LED_PIN    16
#define STATUS_LED_PIN  15
#define NUM_MAIN_LEDS   75
#define NUM_STATUS_LEDS 5
#define LED_TYPE        WS2812B
#define COLOR_ORDER     GRB

// Mic
#define MIC_PIN         34
#define SAMPLES         16

// Buttons
#define BOOT_BUTTON_PIN  0
#define MODE_BUTTON      7
#define COLOR_BUTTON     6
#define BRIGHT_BUTTON    5
#define SAO_BUTTON       4
#define LIGHT_EN        35

// Status LED Colors
#define STATUS_RED     CRGB(255, 0, 0)
#define STATUS_GREEN   CRGB(0, 255, 0)
#define STATUS_BLUE    CRGB(0, 0, 255)
#define STATUS_YELLOW  CRGB(255, 255, 0)
#define STATUS_WHITE   CRGB(255, 255, 255)

#define STATUS_LED_BRIGHTNESS 12

// Battery thresholds
#define WARNING_BATTERY_THRESHOLD 3.5f   // Orange - Warnung
#define LOW_BATTERY_THRESHOLD 3.3f       // Rot - LEDs ausschalten (Main LEDs)
#define BOOST_OFF_THRESHOLD 3.0f         // Boost IC abschalten (LIGHT_EN Pin) - User-Anforderung: bei 3.0V komplett aus
#define DEEP_SLEEP_THRESHOLD 2.9f        // Deep Sleep aktivieren - unter Boost-Off-Schwelle

#endif //GLOBALS_H
