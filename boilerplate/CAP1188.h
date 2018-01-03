#include <Adafruit_Sensor.h>
#include <Adafruit_CAP1188.h>
#include "CONFIG.h"



class CAP1188
{
    public:
        CAP1188(int foo);
        void refreshValues();
        short isTouched();
       bool SensorAvailable;

    private:
        Adafruit_CAP1188 cap;
        uint8_t previous;
};