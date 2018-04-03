#include "OFF_Pin.h"

OFF_Pin::OFF_Pin()
{
    //Constructor code
    pinMode(OFF_PIN, INPUT);
    digitalWrite(OFF_PIN, HIGH);
}

void OFF_Pin::HandleTime(unsigned int  ElapsedTime)
{
    OffPin_Timing += ElapsedTime;
}

bool OFF_Pin::isGrounded()
{
    return (digitalRead(OFF_PIN) == LOW);
}
