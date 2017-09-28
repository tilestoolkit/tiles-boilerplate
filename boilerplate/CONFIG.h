#ifndef CONFIG_h
#define CONFIG_h

#define SUFFIX "Tile_"

#define RFDUINO 1
#define SIMBLEE 2
#define UC RFDUINO

//Devices
#define xAccelerometer_ADXL345 true
#define ACC_INT1_PIN  4 
#define xIMU_LSM9DS0 true
#define xTouch_CAP1188 true
#define xLED_RGB false
#define xLED_NEO true
#define NEO_PIN 2
#define NUM_LEDS 7      //Number of leds in the neopixel strip
#define xDOTM_MATRIX true
#define xHAPTIC_analog false
#define VIBRATING_M_PIN     3 
#define xHAPTIC_IC true


#endif