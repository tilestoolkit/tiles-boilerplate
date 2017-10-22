#include <Adafruit_DRV2605.h>
#include <Wire.h>

class DRV2605
{
    public:
        DRV2605();
        void Vibrate(uint8_t pattern);
       
    private:
        Adafruit_DRV2605 drv;
};