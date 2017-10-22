#include <Arduino.h>
#include "CONFIG.h"

class Template_Device
{
public:
    Template_Device();  //Constructor
    void RefreshValues();   //This should be invoked by Feedbacks/Sensor handler
    void HandleTime(unsigned int ElapsedTime);  //This should be invoked by Feedbacks/Sensor handler
private:
    unsigned int Template_Device_Timing;
    unsigned int RefreshThreshold = 50; //Refresh values every 50ms
};