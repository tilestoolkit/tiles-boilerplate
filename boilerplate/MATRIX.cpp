#include "MATRIX.h"

MATRIX::MATRIX(int i)
{
    //Eyes animation config
    #define MATRIX_EYES         0
  //  blinkIndex = { 1, 2, 3, 4, 3, 2, 1 };   // Blink bitmap sequence (see faces.h)
    blinkCountdown = 100;                    // Countdown to next blink (in frames)
    gazeCountdown  =  75;                    // Countdown to next eye movement
    gazeFrames     =  25;                    // Duration of eye movement (smaller = faster)
    eyeX = 3, eyeY = 3;                        // Current eye position
    newX = 3, newY = 3;                       // Next eye position
    dX   = 0, dY   = 0;                       // Distance from prior to new position

    randomSeed(analogRead(2)); // Seed random number generator from an unused analog input
    matrix.setRotation(1);
    matrix.begin(0x70);
    matrix.setBrightness(15);  // 0 to 15
    matrix.blinkRate(0);      // 0 to 3

}

void MATRIX::start_gazing()
{
  State = BLINKING;
}

void MATRIX::stop_gazing()
{
  State = NO_BLINKING;
}

void MATRIX::face(uint8_t type)
{
  switch(type){
    case 1:
    {
      matrix.clear();
      break;
    }
    case 2:
    {
      matrix.clear();
      matrix.drawBitmap(0,0,dollar,8,8,LED_ON);
      matrix.writeDisplay();   
      break;
    }
  }
}

void MATRIX::face(String type)
{
  stop_gazing();
  matrix.clear();
  if(type == "sad1")
    matrix.drawBitmap(0,0,sad1,8,8,LED_ON);
    else if(type == "sad2")
    matrix.drawBitmap(0,0,sad2,8,8,LED_ON);
    else if(type == "sad3")
    matrix.drawBitmap(0,0,sad3,8,8,LED_ON);
    else if(type == "dollar")
    matrix.drawBitmap(0,0,dollar,8,8,LED_ON);
    else if(type == "happy1")
    matrix.drawBitmap(0,0,happy1,8,8,LED_ON);
    else if(type == "x")
    matrix.drawBitmap(0,0,x,8,8,LED_ON);
    else if(type == "puzzled")
    matrix.drawBitmap(0,0,puzzled,8,8,LED_ON);
    
  matrix.writeDisplay(); 
}

void MATRIX::HandleTime(unsigned int  ElapsedTime)
{
    Matrix_Timing += ElapsedTime;
}

void MATRIX::RefreshValues()
{
    if(State == BLINKING && Matrix_Timing > REFRESH_RATE)
    {
        gazing();
        Matrix_Timing = 0;
    }
}

void MATRIX::gazing()
{
  matrix.clear();
  matrix.drawBitmap(0, 0,
  blinkImg[
  (blinkCountdown < sizeof(blinkIndex)) ?
  blinkIndex[blinkCountdown] :
  0
  ], 8, 8, LED_ON);
  if(--blinkCountdown == 0) blinkCountdown = random(5, 180);
  if(--gazeCountdown <= gazeFrames) {
    matrix.fillRect(
      newX - (dX * gazeCountdown / gazeFrames),
      newY - (dY * gazeCountdown / gazeFrames),
      2, 2, LED_OFF);
    if(gazeCountdown == 0) {
      eyeX = newX; eyeY = newY;
      do {
        newX = random(7); newY = random(7);
        dX   = newX - 3;  dY   = newY - 3;
      } while((dX * dX + dY * dY) >= 10);      
      dX            = newX - eyeX;             // Horizontal distance to move
      dY            = newY - eyeY;             // Vertical distance to move
      gazeFrames    = random(3, 15);           // Duration of eye movement
      gazeCountdown = random(gazeFrames, 120); // Count to end of next movement
    }
  } else {
    matrix.fillRect(eyeX, eyeY, 2, 2, LED_OFF);
  }
  matrix.writeDisplay();
}

