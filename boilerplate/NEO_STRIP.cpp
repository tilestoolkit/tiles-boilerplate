#include "NEO_STRIP.h"


NEO_STRIP::NEO_STRIP()
{
  
  leds.initialize();

}

 // Fill the dots one after the other with a color
 void NEO_STRIP::colorWipe(uint32_t c, uint8_t wait) 
 {
   for(uint16_t i=0; NUM_LEDS; i++) 
   {
       leds.setPixel(i, c);
       leds.render();
       delay(wait);
   }
 }

 void NEO_STRIP::setColor(String color)
 {
    if (color == "off"){
      colorWipe(blinker.packRGB(0,0,0),25);
    } 
    else if (color == "red") {
      colorWipe(blinker.packRGB(255,0,0),25);
      Serial.println("RED");
    }
    else if (color == "green"){
      colorWipe(blinker.packRGB(0,255,0),25);
      Serial.println("GREEN");
      
      } 
    else if (color == "blue"){
      colorWipe(leds.packRGB(0,0,255),25);
  }
    else if (color == "white") {
      colorWipe(leds.packRGB(255,255,255),25);
    }
 }

