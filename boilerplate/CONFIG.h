#ifndef CONFIG_h
#define CONFIG_h

#define SUFFIX "Tile_"

//Devices
#define xAccelerometer_ADXL345 true
#define ACC_INT1_PIN  4

#define xLED_RGB true
#define LED_RED_PIN 0
#define LED_GREEN_PIN 1
#define LED_BLUE_PIN 2
#define LED_TYPE COMMON_CATHODE

#define xLED_NEO false
#define NEO_PIN 2
#define NUM_LEDS 7      //Number of leds in the neopixel strip

#define xDOTM_MATRIX false

#define xHAPTIC_analog true
#define VIBRATING_M_PIN 3 

#define xHAPTIC_IC false


#endif
