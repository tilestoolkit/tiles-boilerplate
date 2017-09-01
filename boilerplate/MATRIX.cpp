#include "MATRIX.h"

MATRIX::MATRIX(int i)
{
    Serial.println("CAP1188 registration started!");
    //matrix = Adafruit_8x8matrix();

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
      } while((dX * dX + dY * dY) >= 10);      // Thank you Pythagoras
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