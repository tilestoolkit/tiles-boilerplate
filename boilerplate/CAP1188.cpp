#include "CAP1188.h"

CAP1188::CAP1188(int foo)
{
    Serial.println("CAP1188 registration started!");
    
    cap = Adafruit_CAP1188(CAP1188_RESET);
    volatile byte interrupt = 0;

      // Initialize capacitive sensor
   if (!cap.begin(0x2B)) {
    Serial.println("CAP1188 not found");
    SensorAvailable = false;
    while (1);
  }
    uint8_t reg = cap.readRegister( 0x1F ) & 0x0F;
    cap.writeRegister( 0x1F, reg | 0x00 );
    pinMode(CAP1188_IRQ, INPUT);
    Serial.println("CAP1188 found!");
    SensorAvailable = true;
    // Turn off multitouch so only one button pressed at a time
    cap.writeRegister(0x2A, 0x80);  // 0x2A default 0x80 use 0x41  — Set multiple touches back to off
    cap.writeRegister(0x41, 0x39);  // 0x41 default 0x39 use 0x41  — Set "speed up" setting back to off
    cap.writeRegister(0x72, 0x00);  // 0x72 default 0x00  — Sets LED links back to off (default)
    cap.writeRegister(0x44, 0x41);  // 0x44 default 0x40 use 0x41  — Set interrupt on press but not release
    cap.writeRegister(0x28, 0x00);  // 0x28 default 0xFF use 0x00  — Turn off interrupt repeat on button hold
  //  RFduino_pinWakeCallback(CAP1188_IRQ, HIGH, callback);

  toogle = false;
}

void CAP1188::refreshValues()
{
    uint8_t touched = cap.touched();
    if(touched > 0 && toogle == false){
    Serial.print("Touched: ");
    Serial.println(touched);
    toogle = true;
  } else 
  {
    toogle = false;
  }}

  short CAP1188::isTouched(){
    uint8_t touched = cap.touched();
    if(touched > 0 && toogle == false){
    Serial.print("Touched: ");
    Serial.println(touched);
    return touched;
    toogle = true;
  } else 
  {
    toogle = false;
    return 0;
  }}