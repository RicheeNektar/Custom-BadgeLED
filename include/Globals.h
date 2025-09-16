#ifndef GLOBALS_H
#define GLOBALS_H

#define VERSION "0.3.0"

#define MAIN_LED_PIN    16
#define STATUS_LED_PIN  15
#define NUM_MAIN_LEDS   75
#define NUM_STATUS_LEDS  5
#define LED_TYPE        WS2812B
#define COLOR_ORDER     GRB

// statusLed[] Indexes
#define STATUS_LED_ID_MAIN       0
#define STATUS_LED_ID_MODE       1
#define STATUS_LED_ID_COLOR      2
#define STATUS_LED_ID_BRIGHTNESS 3
#define STATUS_LED_ID_SAO        4

// Mic
#define MIC_PIN 34
#define SAMPLES 16

// Buttons
#define BOOT_BUTTON_PIN  0
#define MODE_BUTTON      7
#define COLOR_BUTTON     6
#define BRIGHT_BUTTON    5
#define SAO_BUTTON       4
#define LIGHT_EN        35

// Status LED Colors
#define STATUS_RED    CRGB(255,   0,   0)
#define STATUS_GREEN  CRGB(  0, 255,   0)
#define STATUS_BLUE   CRGB(  0,   0, 255)
#define STATUS_YELLOW CRGB(255, 255,   0)
#define STATUS_WHITE  CRGB(255, 255, 255)

// Error Colors
#define ERROR_MODULE_BQ25985    STATUS_RED
#define ERROR_MODULE_AP         STATUS_BLUE
#define ERROR_MODULE_WEB_SERVER STATUS_YELLOW
#define ERROR_MODULE_FS         STATUS_WHITE

#define STATUS_LED_BRIGHTNESS 10

// Error Codes
// BQ25985
#define ERROR_BQ25985_STAT_PIN_BLINK 0xB
#define ERROR_BQ25985_WATCHDOG       0x9
#define ERROR_BQ25985_SAFETY_TIMER   0x2
#define ERROR_BQ25985_SYS_MIN_V      0x4
#define ERROR_BQ25985_JEITA          0x6
#define ERROR_BQ25985_THERMAL_SENSE  0x7
#define ERROR_BQ25985_ADC            0x8
#define ERROR_BQ25985_SET_IN_CURRENT 0x1
#define ERROR_BQ25985_CONNECT_FAULT  0xF
// FS
#define ERROR_FS_LOAD 0xC
#define ERROR_FS_INIT 0xF
// WiFi
#define ERROR_AP_INIT 0xF

// Battery thresholds
#define WARNING_BATTERY_THRESHOLD 3.5f
#define LOW_BATTERY_THRESHOLD     3.3f // LEDs ausschalten (Main LEDs)
#define BOOST_OFF_THRESHOLD       3.0f // Boost IC abschalten (LIGHT_EN)
#define DEEP_SLEEP_THRESHOLD      2.9f // Deep Sleep aktivieren - unter Boost-Off-Schwelle

#endif //GLOBALS_H
