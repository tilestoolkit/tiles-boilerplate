#include "Sensors_Handler.h"

Sensors_Handler::Sensors_Handler(BLE_Handler *Handler)   //default constructor
{
    BLE = Handler;
    EventTriggered = false;
    EventString = String();

    //Accelerometer
    _Accelerometer = NULL;
    Accelerometer_Timing = 0;

    //Compass
    _Compass = NULL;
    Compass_Timing = 0;

    states = 1;
}


void Sensors_Handler::HandleTime(unsigned int ElapsedTime)
{
    Accelerometer_Timing += ElapsedTime;
    Compass_Timing += ElapsedTime;
}

String Sensors_Handler::pollEvent()    // If an event has occured returns the event code
{
   EventString = "";

    if(_AccelerometerAvailable == true && Accelerometer_Timing >= ACCELEROMETER_UPDATE)
    {
        Accelerometer_Timing = 0;
        
        _Accelerometer->RefreshValues();
        
        if (_Accelerometer->isTapped())
        EventString = String("tap,single");
        
        else if (_Accelerometer->isDoubleTapped())
        EventString = String("tap,double");
        
        else if (_Accelerometer->isShaked())
        EventString = String("shake");
        
        //else if (_Accelerometer->isTilted())
        //    EventString = String("tilt");
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

    if(EventString != String(""))
    {  
        Token Event;
        Event.set(EventString);
        BLE->SendEvent(&Event);        
    }  
    return EventString;
}


void Sensors_Handler::setAccelerometer(ADXL345 *Acc)  // Set the private member _Accelerometer with an existing instance of an Accelerometer object
{
    _Accelerometer = Acc;
    _AccelerometerAvailable = Acc->SensorAvailable;
}


void Sensors_Handler::setCompass(Adafruit_HMC5883_Unified *Comp)
{
    _Compass = Comp;
    _CompassAvailable = Comp->begin();
}

