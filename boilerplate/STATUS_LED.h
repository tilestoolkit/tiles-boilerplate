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
private:

    void off_blinking();
    unsigned int Status_Led_Timing;
    unsigned int Led_RefreshThreshold = 500; //Refresh values every 50ms
    bool blink = false;
    bool ledState = false;
};