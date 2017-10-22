#ifndef STATUS_LED_h
#define STATUS_LED_h

#include <Arduino.h>
#include "CONFIG.h"

class STATUS_LED
{
public:
    STATUS_LED();  //Constructor
    void RefreshValues();   //This should be invoked by Feedbacks/Sensor handler
    void HandleTime(unsigned int ElapsedTime);  //This should be invoked by Feedbacks/Sensor handler
    void on();
    void off();
    void blinking();
    void fade2();
private:

    void off_blinking();
    unsigned int Status_Led_Timing;
    unsigned int BlinkingTime = 500; //Refresh values every 50ms
    bool blink = false;
    bool fade = false;
    unsigned int brightness = 0;
    unsigned int  FadeTime = 50;
    unsigned int fadeAmount = 5; 
    bool ledState = false;
};

#endif