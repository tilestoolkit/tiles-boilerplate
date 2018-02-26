#include <Wire.h>
#include "ClosedCube_Si7051.h"

class Temp_Si7051
{
    public:
        Temp_Si7051();
        float read();
        bool SensorAvailable;

    private:
        ClosedCube_Si7051 si7051;
};