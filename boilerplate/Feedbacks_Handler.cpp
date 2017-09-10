#include "Feedbacks_Handler.h"

Feedbacks_Handler::Feedbacks_Handler()
{
    HapticAvailable = false;
    RGB_LEDAvailable = false;
    NEO_STRIPAvailable = false;
    MATRIX_Available = false;
}

// RGB LED
void Feedbacks_Handler::setRGB_LED(RGB_LED *pLED)
{
  LED = pLED;
  RGB_LEDAvailable = true;
}

void Feedbacks_Handler::setColor(String color)
{
  if(RGB_LEDAvailable)
    LED->setColor(color);
  else if(NEO_STRIPAvailable)
    STRIP->setColor(color);
}

// NEOPIXEL LED/STRIP
void Feedbacks_Handler::setNEO_STRIP(NEO_STRIP *pSTRIP)
{
 STRIP = pSTRIP;
 NEO_STRIPAvailable = true;
}

// MATRIX
void Feedbacks_Handler::setMATRIX(MATRIX *pMATRIX)
{
  MATRIXX = pMATRIX;
  MATRIX_Available = true;
}

void Feedbacks_Handler::startGazing()
{
  MATRIXX->start_gazing();
}

void Feedbacks_Handler::stopGazing()
{
  MATRIXX->stop_gazing();
}

void Feedbacks_Handler::showFace(String type)
{
  MATRIXX->face(type);
}

//Haptic Motor
void Feedbacks_Handler::setHapticMotor(Haptic *pHapticMotor)
{
    HapticMotor = pHapticMotor;
    HapticAvailable = true;
}

void Feedbacks_Handler::Vibrate(unsigned int Time)
{  
    if(HapticAvailable == false)
      return;     
    HapticMotor->Vibrate(Time);
}

void Feedbacks_Handler::Vibrate(String Type)
{
    if(HapticAvailable == false)
      return;    
    if(Type == String("short"))
      HapticMotor->VibrateShort();
    else if(Type == String("long"))
      HapticMotor->VibrateLong();
}

//Service Methods
String Feedbacks_Handler::UpdateFeedback()
{
  if(HapticAvailable)
    HapticMotor->RefreshValues();
  if(MATRIX_Available)
    MATRIXX->RefreshValues();
}

void Feedbacks_Handler::HandleTime(unsigned int ElapsedTime)
{
  if(HapticAvailable)
    HapticMotor->HandleTime(ElapsedTime);
  if(MATRIX_Available)
    MATRIXX->HandleTime(ElapsedTime);

    //Serial.print("Elapsed Time: "); Serial.println(ElapsedTime);
} 

