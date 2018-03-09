#ifndef CONFIG_h
#define CONFIG_h

#define SUFFIX "Tile_"

#define TILES_SQUARE  1
#define TILES_TEMP  2

// Set your device here ///
#define DEVICE TILES_SQUARE
///////////////////////////

#if DEVICE == TILES_SQUARE
    #define xAccelerometer_ADXL345 true
    #define ACC_INT1_PIN  7
    #define xIMU_LSM9DS0 false
    #define xTouch_CAP1188 true
    #define CAP1188_RESET  29
    #define CAP1188_IRQ 28
    #define STATUS_LED_PIN 30
    #define BUTTON_PIN 5
    #define xLED_RGB true
    #define PIN_LED_RED 16
    #define PIN_LED_GREEN 15
    #define PIN_LED_BLUE 11
    #define LED_TYPE COMMON_ANODE
    #define xLED_NEO false
    #define NEO_PIN 27
    #define NUM_LEDS 3      //Number of leds in the neopixel strip
    #define xDOTM_MATRIX false

    #define xHAPTIC_analog false
    #define VIBRATING_M_PIN     3 

    #define xHAPTIC_IC true

    #define xTemp_Si7051 false
    #define xHum_HDC2010 false
    #define OFF_PIN 14
    #define xOFF_PIN false
#elif DEVICE == TILES_TEMP
    #define xTemp_Si7051 true
    #define xHum_HDC2010 true
    #define xOFF_PIN true
    #define OFF_PIN 14
    #define xLED_RGB true
    #define PIN_LED_RED 2
    #define PIN_LED_GREEN 3
    #define PIN_LED_BLUE 4
    #define LED_TYPE COMMON_ANODE

    #define xAccelerometer_ADXL345 false
    #define ACC_INT1_PIN  7
    #define xIMU_LSM9DS0 false
    #define xTouch_CAP1188 false
    #define CAP1188_RESET  29
    #define CAP1188_IRQ 28
    #define STATUS_LED_PIN 30
    #define BUTTON_PIN 5
    #define xLED_NEO false
    #define NEO_PIN 27
    #define NUM_LEDS 3      //Number of leds in the neopixel strip
    #define xDOTM_MATRIX false

    #define xHAPTIC_analog false
    #define VIBRATING_M_PIN     3 

    #define xHAPTIC_IC false
#endif


// //Devices
// #define xAccelerometer_ADXL345 false
// #define ACC_INT1_PIN  7 

// #define xIMU_LSM9DS0 false

// #define xTouch_CAP1188 false
// #define CAP1188_RESET  29
// #define CAP1188_IRQ 28

// #define xTemp_Si7051 true
// #define xHum_HDC2010 true

// #define STATUS_LED_PIN 30

// #define xOFF_PIN true
// #define OFF_PIN 14

// #define BUTTON_PIN 5

// #define xLED_RGB true
// #define PIN_LED_RED 2
// #define PIN_LED_GREEN 3
// #define PIN_LED_BLUE 4
// #define LED_TYPE COMMON_ANODE

// #define xLED_NEO false
// #define NEO_PIN 27
// #define NUM_LEDS 3      //Number of leds in the neopixel strip

// #define xDOTM_MATRIX false

// #define xHAPTIC_analog false
// #define VIBRATING_M_PIN     3 

// #define xHAPTIC_IC false
#endif
