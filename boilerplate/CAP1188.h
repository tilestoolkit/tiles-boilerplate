#include <Adafruit_Sensor.h>
#include <Adafruit_CAP1188.h>

#define CAP1188_RESET  11
#define CAP1188_IRQ 7


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