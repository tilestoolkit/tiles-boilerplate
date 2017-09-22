#include <Arduino.h>
#include <Ai_RFD_WS2812.h>
#include "CONFIG.h"

class NEO_STRIP
{
    public:
        NEO_STRIP();
        void colorWipe(uint32_t c, uint8_t wait);
        void set_Color(String color);
        void blink(String color);

        void RefreshValues();
        void HandleTime(unsigned int ElapsedTime);
       
    private:
        bool state;
        bool blinking;
        bool ledState = false;
        String blinkingColor;

        unsigned int  Blink_Timing;
        unsigned int  BlinkingTime = 500;

        RFD_WS2812 leds = RFD_WS2812(NUM_LEDS, NEO_PIN);
        //RFD_WS2812 leds;
};

