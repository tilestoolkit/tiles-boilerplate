#include <Arduino.h>
#include <Ai_RFD_WS2812.h>
#include "CONFIG.h"

class NEO_STRIP
{
    public:
        NEO_STRIP();
        void colorWipe(uint32_t c, uint8_t wait);
        void setColor(String color);
        void blink(String color);
        void fade(String color);

        void RefreshValues();
        void HandleTime(unsigned int ElapsedTime);
       
    private:
        bool state;
        bool blinking;
        bool fading;
        bool ledState = false;
        String blinkingColor;

        unsigned int  LED_Timing;
        unsigned int  BlinkingTime = 500;
        unsigned int  FadingTime = 50;
        
        unsigned int fadeAmount = 10;
        unsigned int curr_r = 0;
        unsigned int curr_g = 0;
        unsigned int curr_b = 0;
        unsigned int target_r = 0;
        unsigned int target_g = 0;
        unsigned int target_b = 0;
        unsigned int counter = 0;

        RFD_WS2812 leds = RFD_WS2812(NUM_LEDS, NEO_PIN);
        //RFD_WS2812 leds;
};

