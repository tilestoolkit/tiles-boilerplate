#ifndef CONFIG_h
#define CONFIG_h

#define SUFFIX "Tile_"
#define RFDUINO 1
#define SIMBLEE 2
#define UC RFDUINO

//#define COMMON_ANODE  1
//#define COMMON_CATHODE  2
//#define LED_TYPE COMMON_CATHODE

// TOKEN FIRMWARE METADATA
#define NAME    "AnyBoard Pawn"
#define VERSION "0.1"
#define UUID    "3191-6275-32g4"

// Status commands
const uint8_t GET_NAME             = 32;

#define xAccelerometer_ADXL345 true
#define xIMU_LSM9DS0 true
#define xTouch_CAP1188 true
#define xLED_RGB false
#define xLED_NEO true
#define NEO_PIN 2
#define NUM_LEDS 7      //Number of leds in the neopixel strip
#define xDOTM_MATRIX true
#define xHAPTIC_analog false


#endif