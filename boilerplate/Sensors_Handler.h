#include "ADXL345.h"
#include "LSM9DS0.h"
#include "CAP1188.h"
#include "Temp_Si7051.h"
#include "BLE_Handler.h"


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

    private:
      bool EventTriggered;      // True if an event has occured, else false. Reset on read with pollEvent();
      String EventString;       // Event code according to protocol.h
      bool _InertialCentralAvailable;
      bool _AccelerometerAvailable;
      bool _TouchSensorAvailable;
      bool _TempSensorAvailable;
      BLE_Handler *BLE;
      int states;
      void state_change();

      //Accelrometer
      ADXL345 *_Accelerometer;            // Handle an accelerometer object
      #define ACCELEROMETER_UPDATE  100   //Accelerometer refresh period
      unsigned int Accelerometer_Timing;
      
      //Sensors source of TokenSoloEvent
      LSM9DS0 *_InertialCentral;
      #define INERTIAL_CENTRAL_UPDATE  100   //Accelerometer refresh period
      unsigned int InertialCentral_Timing;

      //Sensors source of TokenSoloEvent
      CAP1188 *_TouchSensor;
      #define TOUCHSENSOR_UPDATE  100   //Accelerometer refresh period
      unsigned int TouchSensor_Timing;

      //Temperature sensor
      Temp_Si7051 *_TempSensor;
      #define TEMP_UPDATE  100   //Accelerometer refresh period
      unsigned int Temp_Timing;
};

