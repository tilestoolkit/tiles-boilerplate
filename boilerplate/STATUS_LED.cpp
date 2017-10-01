#include "STATUS_LED.h"

STATUS_LED::STATUS_LED()
{
    //Constructor code
    pinMode(STATUS_LED_PIN, OUTPUT);
}

void STATUS_LED::HandleTime(unsigned int  ElapsedTime)
{
    Status_Led_Timing += ElapsedTime;
}

void STATUS_LED::on()
{
    digitalWrite(STATUS_LED_PIN,HIGH);
}

void STATUS_LED::off()
{
    digitalWrite(STATUS_LED_PIN,LOW);
    blink = false;
}

void STATUS_LED::off_blinking()
{
    digitalWrite(STATUS_LED_PIN,LOW);
    
}

void STATUS_LED::blinking()
{
    blink = true;
}

void STATUS_LED::fade2()
{
    fade = true;
    blink = false;
}

void STATUS_LED::RefreshValues()
{
    if(blink == true && Status_Led_Timing > BlinkingTime)
    {
      if (ledState == false) {
        ledState = true;
      } else {
        ledState = false;
      }
      if (ledState == false)
        off_blinking();
      else
        on();
    Status_Led_Timing = 0;
    }

    else if(fade == true && Status_Led_Timing > FadeTime)
    {
        analogWrite(STATUS_LED_PIN,brightness);
        brightness = brightness + fadeAmount;
        if (brightness <= 0 || brightness >= 255) {
            fadeAmount = -fadeAmount;
          }
        Status_Led_Timing = 0;
    }


}