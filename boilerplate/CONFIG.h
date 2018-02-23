#ifndef CONFIG_h
#define CONFIG_h

#define SUFFIX "Tile_"

//Devices
#define xAccelerometer_ADXL345 false
#define ACC_INT1_PIN  7 

#define xIMU_LSM9DS0 false

#define xTouch_CAP1188 false
#define CAP1188_RESET  29
#define CAP1188_IRQ 28

#define STATUS_LED_PIN 30

#define BUTTON_PIN 5

#define xLED_RGB true
#define PIN_LED_RED 2
#define PIN_LED_GREEN 3
#define PIN_LED_BLUE 4
#define LED_TYPE COMMON_ANODE

#define xLED_NEO false
#define NEO_PIN 27
#define NUM_LEDS 3      //Number of leds in the neopixel strip

#define xDOTM_MATRIX false

#define xHAPTIC_analog false
#define VIBRATING_M_PIN     3 

#define xHAPTIC_IC false
#endif
