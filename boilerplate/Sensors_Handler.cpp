#include "Sensors_Handler.h"

Sensors_Handler::Sensors_Handler(BLE_Handler *Handler)   //default constructor
{
    BLE = Handler;
    EventTriggered = false;
    EventString = String();

    //Accelerometer
    _Accelerometer = NULL;
    Accelerometer_Timing = 0;

    //InertialCentral
    _InertialCentral = NULL;
    InertialCentral_Timing = 0;

    //Compass
    _Compass = NULL;
    Compass_Timing = 0;

    //TouchController
    _TouchSensor = NULL;
    TouchSensor_Timing = 0;

    //Light
    _Light = NULL;
    Light_Timing = 0;

    //Temperature
    _TempSensor = NULL;
    Temp_Timing = 0;
    
    //Humidity
    _HumSensor = NULL;
    Hum_Timing = 0;

    //OFF pin
    _OffPin = NULL;
    Off_Timing = 0;

    states = 1;
}


void Sensors_Handler::HandleTime(unsigned int ElapsedTime)
{
    Compass_Timing += ElapsedTime;
    Light_Timing += ElapsedTime;
    Accelerometer_Timing += ElapsedTime;  
    InertialCentral_Timing += ElapsedTime;
    TouchSensor_Timing += ElapsedTime;
    Temp_Timing += ElapsedTime;
    Hum_Timing += ElapsedTime;
    Off_Timing += ElapsedTime;
    _InertialCentral->HandleTime(ElapsedTime);
}

String Sensors_Handler::pollEvent()    // If an event has occured returns the event code
{
   EventString = "";

    if(_AccelerometerAvailable == true && Accelerometer_Timing >= ACCELEROMETER_UPDATE)
    {
        //Serial.println("ACC UPDATE");
        Accelerometer_Timing = 0;
        
        _Accelerometer->RefreshValues();
        
        if (_Accelerometer->isTapped())
        EventString = String("tap,single");
        
        else if (_Accelerometer->isDoubleTapped())
        EventString = String("tap,double");
        
        else if (_Accelerometer->isShaked())
        EventString = String("shake");
        
        else if (_Accelerometer->isTilted())
        EventString = String("tilt");
    }

    if(_CompassAvailable == true && Compass_Timing >= COMPASS_UPDATE)
    {

        Compass_Timing = 0;

        sensors_event_t event; 
        _Compass->getEvent(&event);

        float heading = atan2(event.magnetic.y, event.magnetic.x);
        float declinationAngle = -0.0567; //Declination Angle for Trondheim, 2018
        heading += declinationAngle;

        if(heading < 0)
        heading += 2*PI;
    
        if(heading > 2*PI)
        heading -= 2*PI;
   
        float headingDegrees = heading * 180/M_PI; 
  
//        Serial.print("Heading (degrees): "); Serial.println(headingDegrees);
       
        if (headingDegrees < 5 || headingDegrees > 355)
          EventString = String("heading,N");

        else if (85 < headingDegrees && headingDegrees < 95)
          EventString = String("heading,E");

        else if (175 < headingDegrees && headingDegrees < 185)
          EventString = String("heading,S");

        else if (265 < headingDegrees && headingDegrees < 275)
          EventString = String("heading,W");
  }


    if(_InertialCentralAvailable == true && InertialCentral_Timing >= ACCELEROMETER_UPDATE){
        InertialCentral_Timing = 0;
        short isRotated = _InertialCentral->isRotated();
        
        _InertialCentral->RefreshValues();
        
        if (_InertialCentral->isTapped())
            EventString = String("tap");
        
        else if (_InertialCentral->isDoubleTapped())
            EventString = String("doubletap");
        
        else if (_InertialCentral->isShaked()){}
           // EventString = String("shake");
        
        else if (_InertialCentral->isTilted())
            EventString = String("tilt");
         else if(isRotated != 0)
         {
             if(isRotated == 1)
                 EventString = String("clockrot");
             else if(isRotated == -1)
                 EventString = String("cclockrot");
         }
    }

    if(_LightAvailable == true && Light_Timing >= LIGHT_UPDATE)
    {
       Light_Timing = 0;

//        Serial.println(_Light->readVisibleLux()); // from 0 to 9000 with very bright torch light
       lux = _Light->readVisibleLux();

       if (lux > 700) EventString = String("light,very bright");
       else if (lux > 300) EventString = String("light,bright");
       else if (lux > 0) EventString = String("light,normal");
       else if (lux == 0) EventString = String("light,dark");
    }


     if(_TouchSensorAvailable == true && TouchSensor_Timing >= TOUCHSENSOR_UPDATE){
        TouchSensor_Timing = 0;
        short touchpin = _TouchSensor->isTouched();
        if(touchpin == 2) EventString = String("touched,B");
        else if(touchpin == 1) EventString = String("touched,A");
    }

    if(_TempSensorAvailable == true && Temp_Timing >= TEMP_UPDATE)
    {
        Temp_Timing = 0;
        float round_temp = roundf(_TempSensor->read() * 10) / 10; //round to first decimal
        String t = String(round_temp);
        
        EventString = String("temp," + t.substring(0, t.length()-1)); //remove second decimal (printed as 0 after round) from string
    }

    if(_HumSensorAvailable == true && Hum_Timing >= HUM_UPDATE)
    {
        Hum_Timing = 0;
        
        // String t = String(round_temp);
        // EventString = String("ht," + );
        EventString = String("humi," + _HumSensor->read()); //remove second decimal (printed as 0 after round) from string
    }

    if(_OffPinAvailable == true && Off_Timing >= OFF_UPDATE)
    {
        // turn on red led on shutdown
        Off_Timing = 0;
        if(_OffPin->isGrounded()){
            digitalWrite(PIN_LED_RED, LOW);
            delay(2000);
            digitalWrite(PIN_LED_RED, HIGH);
            if(BT_LED) digitalWrite(BT_LED, LOW);
            BLE->shutdown();
        }
    }
    

    if(EventString != String(""))
    {  
        Token Event = Token(EventString);
        BLE->SendEvent(&Event);
    }  
    return EventString;
}


void Sensors_Handler::setAccelerometer(ADXL345 *Acc)  // Set the private member _Accelerometer with an existing instance of an Accelerometer object
{
    _Accelerometer = Acc;
    _AccelerometerAvailable = Acc->SensorAvailable;
}

void Sensors_Handler::setInertialCentral(LSM9DS0 *InC)
{
    _InertialCentral = InC;
    _InertialCentralAvailable = InC->SensorAvailable;
}

void Sensors_Handler::setCompass(Adafruit_HMC5883_Unified *Comp)
{
    _Compass = Comp;
    _CompassAvailable = Comp->begin();
}

void Sensors_Handler::setTempSensor(Temp_Si7051 *Temp)
{
    _TempSensor = Temp;
    _TempSensorAvailable = true;
}

void Sensors_Handler::setHumSensor(Hum_HDC2010 *Hum)
{
    _HumSensor = Hum;
    _HumSensorAvailable = true;
}

void Sensors_Handler::setTouchSensor(CAP1188 *Touch) 
{
    _TouchSensor = Touch;
    _TouchSensorAvailable = true;
}

void Sensors_Handler::setOffPin(OFF_Pin *Off)
{
    _OffPin = Off;
    _OffPinAvailable = true;
}

void Sensors_Handler::state_change()
{
    extern Feedbacks_Handler feedback_handle;
    switch(states){
        case 1:
        feedback_handle.showFace("happy1");
        states++;
        break;
        case 2:
        feedback_handle.showFace("dollar");
        states++;
        break;
        case 3:
        feedback_handle.showFace("puzzled");
        states++;
        break;
        case 4:
        feedback_handle.showFace("sad1");
        states++;
        break;
        case 5:
        feedback_handle.showFace("sad2");
        states++;
        break;
        case 6:
        feedback_handle.showFace("sad3");
        states++;
        break;
        case 7:
        feedback_handle.showFace("x");
        states++;
        break;
        case 8:
        feedback_handle.startGazing();
        states=1;
        break;
    }
    
}

void Sensors_Handler::setLight(TSL2561_CalculateLux *Light)
{
    _Light = Light;
    Light->init();
    _LightAvailable = true;
}

