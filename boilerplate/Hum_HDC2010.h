#include "HDC2010.h"

#define ADDR 0x41

class Hum_HDC2010
{
    public:
        Hum_HDC2010();
        String read();
        bool SensorAvailable;

    private:
        HDC2010 hdc2010 = HDC2010(ADDR);
        float temperature;
        float humidity;
};