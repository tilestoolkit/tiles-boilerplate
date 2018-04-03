#if !defined(OFF_Pin_h)
#define OFF_Pin_h

#include <Arduino.h>
#include "CONFIG.h"

class OFF_Pin
{
public:
    OFF_Pin();  //Constructor
    void RefreshValues();   //This should be invoked by Feedbacks/Sensor handler
    void HandleTime(unsigned int ElapsedTime);  //This should be invoked by Feedbacks/Sensor handler
    bool isGrounded();
private:
    unsigned int OffPin_Timing;
};

#endif