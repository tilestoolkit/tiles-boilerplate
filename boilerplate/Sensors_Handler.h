#include "ADXL345.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <Digital_Light_TSL2561.h>
#include "LSM9DS0.h"
#include "CAP1188.h"
#include "Temp_Si7051.h"
#include "BLE_Handler.h"
#include "Hum_HDC2010.h"
#include "OFF_Pin.h"


class Sensors_Handler
{
    public:
      Sensors_Handler(BLE_Handler *Handler);      //default constructor
      String pollEvent();                         // If an event has occured returns the event code
      void HandleTime(unsigned int ElapsedTime);   
      void setAccelerometer(ADXL345 *Acc);  // Set the private member _Accelerometer with an existing instance of an Accelerometer object
      void setCompass(Adafruit_HMC5883_Unified *Comp);
      void setLight(TSL2561_CalculateLux *Light);
      void setInertialCentral(LSM9DS0 *InC);
      void setTouchSensor(CAP1188 *Touch);
      void setTempSensor(Temp_Si7051 *Temp);
      void setHumSensor(Hum_HDC2010 *Hum);
      void setOffPin(OFF_Pin *Off);

    private:
      bool EventTriggered;      // True if an event has occured, else false. Reset on read with pollEvent();
      String EventString;       // Event code according to protocol.h
      bool _InertialCentralAvailable;
      bool _TouchSensorAvailable;
      bool _TempSensorAvailable;
      bool _HumSensorAvailable;
      bool _OffPinAvailable;
      BLE_Handler *BLE;
      int states;
      void state_change();

      //Accelrometer
      bool _AccelerometerAvailable;
      int tilt_a;
      ADXL345 *_Accelerometer;            // Handle an accelerometer object
      #define ACCELEROMETER_UPDATE  100   // refresh period
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

      
      //Sensors source of TokenSoloEvent
      LSM9DS0 *_InertialCentral;
      #define INERTIAL_CENTRAL_UPDATE  100   // refresh period
      unsigned int InertialCentral_Timing;

      //Sensors source of TokenSoloEvent
      CAP1188 *_TouchSensor;
      #define TOUCHSENSOR_UPDATE  100   // refresh period
      unsigned int TouchSensor_Timing;

      //Temperature sensor
      Temp_Si7051 *_TempSensor;
      #define TEMP_UPDATE  10000   // refresh period
      unsigned int Temp_Timing;
      
      //Humidity sensor
      Hum_HDC2010 *_HumSensor;
      #define HUM_UPDATE  4000   // refresh period
      unsigned int Hum_Timing;

      //OFF pim
      OFF_Pin *_OffPin;
      #define OFF_UPDATE  500   // refresh period
      unsigned int Off_Timing;
};

