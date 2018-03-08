#include "ADXL345.h"
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
      void setInertialCentral(LSM9DS0 *InC);  // Set the private member _Accelerometer with an existing instance of an Accelerometer object
      void setTouchSensor(CAP1188 *Touch);
      void setTempSensor(Temp_Si7051 *Temp);
      void setHumSensor(Hum_HDC2010 *Hum);
      void setOffPin(OFF_Pin *Off);

    private:
      bool EventTriggered;      // True if an event has occured, else false. Reset on read with pollEvent();
      String EventString;       // Event code according to protocol.h
      bool _InertialCentralAvailable;
      bool _AccelerometerAvailable;
      bool _TouchSensorAvailable;
      bool _TempSensorAvailable;
      bool _HumSensorAvailable;
      bool _OffPinAvailable;
      BLE_Handler *BLE;
      int states;
      void state_change();

      //Accelrometer
      ADXL345 *_Accelerometer;            // Handle an accelerometer object
      #define ACCELEROMETER_UPDATE  100   // refresh period
      unsigned int Accelerometer_Timing;
      
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

