#include <Arduino.h>
//#include "FastLED.h"
#include <Ai_RFD_WS2812.h>

#define NEO_PIN 2
#define NUM_LEDS 7      //Number of leds in the neopixel strip


class NEO_STRIP
{
    public:
        NEO_STRIP();
        void colorWipe(uint32_t c, uint8_t wait);
        void set_Color(String color);
       

    private:
        bool state;
        RFD_WS2812 leds = RFD_WS2812(NUM_LEDS, NEO_PIN);
        //RFD_WS2812 leds;
};

