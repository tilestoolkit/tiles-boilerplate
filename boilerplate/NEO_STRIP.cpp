#include "NEO_STRIP.h"

NEO_STRIP::NEO_STRIP()
{
  //Serial.println("LED0");
 // leds = RFD_WS2812(7, 2);
  leds.initialize();
  colorWipe(leds.packRGB(0,0,255),25);
  //Serial.println("LED1");
  delay(500);
  colorWipe(leds.packRGB(0,0,0),25);
 // Serial.println("LED2");
}

// Fill the dots one after the other with a color
void NEO_STRIP::colorWipe(uint32_t c, uint8_t wait) 
{
  for(uint16_t i=0; i<leds.getNumPixels(); i++) 
  {
      leds.setPixel(i, c);
      leds.render();
      delay(wait);
  }
}

 void NEO_STRIP::set_Color(String color)
 {
    if (color == "off"){
      colorWipe(leds.packRGB(0,0,0),25);
    } 
    else if (color == "red") {
      colorWipe(leds.packRGB(255,0,0),25);
      Serial.println("RED");
    }
    else if (color == "green"){
      colorWipe(leds.packRGB(0,255,0),25);
      Serial.println("GREEN");
      } 
    else if (color == "blue"){
      colorWipe(leds.packRGB(0,0,255),25);
  }
    else if (color == "white") {
      colorWipe(leds.packRGB(255,255,255),25);
    }
 }

