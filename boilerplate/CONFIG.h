#ifndef CONFIG_h
#define CONFIG_h

#define SUFFIX "Tile_"

//Devices
#define xAccelerometer_ADXL345 true
#define ACC_INT1_PIN  28 

#define xIMU_LSM9DS0 false

#define xTouch_CAP1188 true

#define STATUS_LED_PIN 19

#define BUTTON_PIN 16

#define xLED_RGB false
#define LED_RED_PIN 0
#define LED_GREEN_PIN 1
#define LED_BLUE_PIN 2
#define LED_TYPE COMMON_ANODE

#define xLED_NEO false
#define NEO_PIN 29
#define NUM_LEDS 1      //Number of leds in the neopixel strip

#define xDOTM_MATRIX false

#define xHAPTIC_analog false
#define VIBRATING_M_PIN     3 

#define xHAPTIC_IC true


#endif