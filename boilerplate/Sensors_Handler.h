#include "ADXL345.h"
#include "BLE_Handler.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <Digital_Light_TSL2561.h>

class Sensors_Handler
{
    public:
      Sensors_Handler(BLE_Handler *Handler);      //default constructor
      String pollEvent();                         // If an event has occured returns the event code
      void HandleTime(unsigned int ElapsedTime);   
      void setAccelerometer(ADXL345 *Acc);  // Set the private member _Accelerometer with an existing instance of an Accelerometer object
      void setCompass(Adafruit_HMC5883_Unified *Comp);
      void setLight(TSL2561_CalculateLux *Light);

    private:
      bool EventTriggered;      // True if an event has occured, else false. Reset on read with pollEvent();
      String EventString;       // Event code according to protocol.h
      BLE_Handler *BLE;
      int states;
      void state_change();

      //Accelrometer
      bool _AccelerometerAvailable;
      ADXL345 *_Accelerometer;            // Handle an accelerometer object
      #define ACCELEROMETER_UPDATE  100   //Accelerometer refresh period
      unsigned int Accelerometer_Timing;

      //Magnetometer/compass
      bool _CompassAvailable;
      Adafruit_HMC5883_Unified *_Compass;
      #define COMPASS_UPDATE 650
      unsigned int Compass_Timing;

      //Light
      bool _LightAvailable;
      TSL2561_CalculateLux *_Light;
      #define LIGHT_UPDATE 950
      unsigned int Light_Timing;
      signed long lux;

};

