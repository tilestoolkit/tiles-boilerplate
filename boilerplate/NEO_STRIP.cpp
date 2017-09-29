#include "NEO_STRIP.h"

NEO_STRIP::NEO_STRIP()
{
  leds.initialize();
  colorWipe(leds.packRGB(0,0,255),25);
  delay(500);
  colorWipe(leds.packRGB(0,0,0),25);
}

// Fill the dots one after the other with a color
 void NEO_STRIP::setColor(String color)
 {
    if (color == "off"){
      colorWipe(leds.packRGB(0,0,0),25);
      blinking = false;
      fading = false;
    } 
    else if (color == "red") {
      colorWipe(leds.packRGB(255,0,0),25);
    }
    else if (color == "green"){
      colorWipe(leds.packRGB(0,255,0),25);
      } 
    else if (color == "blue"){
      colorWipe(leds.packRGB(0,0,255),25);
  }
    else if (color == "white") {
      colorWipe(leds.packRGB(255,255,255),25);
    }
    else if (color == "black") {
      colorWipe(leds.packRGB(0,0,0),25);
    }
 }

 void NEO_STRIP::blink(String color){
  blinking = true;
  fading = false;
  blinkingColor = color;
 }

 void NEO_STRIP::fade(String color){
  fading = true;
  setColor("black");
  leds.clear();
  curr_b = 0;
  curr_g = 0;
  curr_r = 0;
  if (color == "red") {
    target_r = 255;
    target_g = 0;
    target_b = 0; }
  else if (color == "green"){
    target_r = 0;
    target_g = 255;
    target_b = 0;    } 
  else if (color == "blue"){
    target_r = 0;
    target_g = 0;
    target_b = 255;}
  else if (color == "white") {
    target_r = 255;
    target_g = 255;
    target_b = 255;  }
 }

 void NEO_STRIP::colorWipe(uint32_t c, uint8_t wait) 
 {
   for(uint16_t i=0; i<leds.getNumPixels(); i++) 
   {
       leds.setPixel(i, c);
       leds.render();
       delay(wait);
   }
 }

//Service methods
void NEO_STRIP::HandleTime(unsigned int  ElapsedTime)
{
    LED_Timing += ElapsedTime;
}

void NEO_STRIP::RefreshValues()
{
    if(blinking == true && LED_Timing > BlinkingTime)
    {
      if (ledState == false) {
        ledState = true;
      } else {
        ledState = false;
      }
      if (ledState == false)
        setColor("black");
      else
        setColor(blinkingColor);
      LED_Timing = 0;
    }

    if(fading == true && LED_Timing > FadingTime)
    {       
      if(target_r == 255){
        curr_r = curr_r +fadeAmount;}
      if(target_g == 255){
        curr_g = curr_g +fadeAmount;}
      if(target_b == 255){
        curr_b = curr_b +fadeAmount;}
      counter = counter + fadeAmount;
      colorWipe(leds.packRGB(curr_r, curr_g, curr_b),10);  // set the color
      if(counter <= 0 || counter >= 230){
        fadeAmount = -fadeAmount;
      }
      LED_Timing = 0;
    }
}