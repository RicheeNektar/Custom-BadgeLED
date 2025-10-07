#ifndef GLOBALS_H
#define GLOBALS_H

#define VERSION "v0.7.0"
#define iVERSION 0x00000700 // first byte unused

// Pins
// LED
#define LIGHT_EN        35
#define MAIN_LED_PIN    16
#define STATUS_LED_PIN  15
// Display Pins
#define EINK_SDA  11
#define EINK_SCL  12
#define EINK_BUSY 13
#define EINK_RES   8
#define EINK_DC    9
#define EINK_CS   10
// Buttons
#define BOOT_BUTTON_PIN   0
#define MODE_BUTTON_PIN   7
#define COLOR_BUTTON_PIN  6
#define BRIGHT_BUTTON_PIN 5
#define SAO_BUTTON_PIN    4

// Mic
#define MIC_PIN 34
#define SAMPLES 16

// Button events
#define BUTTON_COOLDOWN_m             100000
#define BUTTON_LONG_PRESS_COOLDOWN_m  250000
#define BUTTON_LONG_PRESS_DURATION_m 1500000

// statusLed[] Indexes
#define STATUS_LED_ID_MAIN       0
#define STATUS_LED_ID_MODE       1
#define STATUS_LED_ID_COLOR      2
#define STATUS_LED_ID_BRIGHTNESS 3
#define STATUS_LED_ID_SAO        4

// buttons[] Indexes
#define BUTTON_ID_BOOT 0
#define BUTTON_ID_MODE 1
#define BUTTON_ID_COLOR 2
#define BUTTON_ID_BRIGHTNESS 3
#define BUTTON_ID_SAO 4

#define NUM_BUTTONS      5
#define NUM_MAIN_LEDS   75
#define NUM_STATUS_LEDS  5
#define LED_TYPE        WS2812B
#define COLOR_ORDER     GRB

// Status LED Colors
#define STATUS_OFF    CRGB(  0,   0,   0)
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
#define ERROR_FS_LOAD  0xC
#define ERROR_FS_WRITE 0x7
#define ERROR_FS_INIT  0xF
// WiFi
#define ERROR_AP_INIT 0xF

// Battery thresholds
#define WARNING_BATTERY_THRESHOLD 3.5f
#define LOW_BATTERY_THRESHOLD     3.3f // LEDs ausschalten (Main LEDs)
#define BOOST_OFF_THRESHOLD       3.0f // Boost IC abschalten (LIGHT_EN)
#define DEEP_SLEEP_THRESHOLD      2.9f // Deep Sleep aktivieren - unter Boost-Off-Schwelle

#endif //GLOBALS_H
