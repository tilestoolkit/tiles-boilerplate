#include <Adafruit_DRV2605.h>
#include <Wire.h>

// Usable vibration patterns from datasheet

// #define SOFT_BUMP               7
// #define SOFT_FUZZ               13
#define STRONG_FUZZ             14
#define SHORT_ALERT             15
// #define LONG_ALERT              16
// #define BUZZ                    47
// #define PULSE                   52
// #define TRANS_CLICK             58
// #define TRANS_HUM               64
// #define TRANS_RAMP_DOWN         70
#define TRANS_RAMP_UP           82
// #define TRANS_RAMP_UP_LONG      88
#define TRANS_RAMP_DOWN_50      94
// #define TRANS_RAMP_UP_50        106
// #define TRANS_RAMP_UP_50_LONG   108
#define LONG_BUZZ               118
#define SMOOTH_HUM              119

class DRV2605
{
    public:
        DRV2605();
        void Vibrate(uint8_t pattern);
        void burst();
        void shortv();
        void longv();
        void raise();
        void fall();
        void raiseFall();

    private:
        Adafruit_DRV2605 drv;
        void delay(uint8_t step, uint8_t ms);
};