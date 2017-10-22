#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#define BLINKING true
#define NO_BLINKING false

class MATRIX
{
    public: 
        MATRIX(int i);
        void start_gazing();
        void stop_gazing();
        void face(uint8_t type);
        void face(String type);
        void RefreshValues();
        void HandleTime(unsigned int ElapsedTime);

    private:
        Adafruit_8x8matrix matrix = Adafruit_8x8matrix();;
        uint8_t blinkIndex[7] = { 1, 2, 3, 4, 3, 2, 1 };
        uint8_t  blinkCountdown;
        uint8_t  gazeCountdown;
        uint8_t  gazeFrames;
        int8_t eyeX, eyeY;                        
        int8_t  newX, newY;  
        int8_t  dX, dY;       

        unsigned int  Matrix_Timing;
        bool State;       
        void gazing();
        
        #define REFRESH_RATE 10 //half frequence because of the 10ms delay in the loop
};

static const uint8_t PROGMEM
blinkImg[][8] = {    // Eye animation frames
{ B00111100,         // Fully open eye
B01111110,
B11111111,
B11111111,
B11111111,
B11111111,
B01111110,
B00111100 },
{ B00000000,
B01111110,
B11111111,
B11111111,
B11111111,
B11111111,
B01111110,
B00111100 },
{ B00000000,
B00000000,
B00111100,
B11111111,
B11111111,
B11111111,
B00111100,
B00000000 },
{ B00000000,
B00000000,
B00000000,
B00111100,
B11111111,
B01111110,
B00011000,
B00000000 },
{ B00000000,         // Fully closed eye
B00000000,
B00000000,
B00000000,
B10000001,
B01111110,
B00000000,
B00000000 } },
dollar[]=
{ B00010100,
  B00111110,
  B01010100,
  B01010100,
  B00111110,
  B00010101,
  B00010101,
  B00111110
},
dollarALT[]=
{ B00011000,
  B01111110,
  B01011000,
  B01111110,
  B00011010,
  B01111110,
  B01111110,
  B00011000
},
happy1[]=
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00111100,
  B01111110,
  B11000011,
  B11000011
},
x[]=
{
  B10000001,
  B01000010,
  B00100100,
  B00011000,
  B00011000,
  B00100100,
  B01000010,
  B10000001
},
puzzled[]=
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00100000,
  B01010100,
  B00001000,
  B00000000
},
sad1[]=
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00111000,
  B01111100,
  B00111000,
  B00000000
},
sad2[]={
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00111000,
  B00000000
},
sad3[]={
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000110,
  B00001111,
  B00001111,
  B00000110
},
test[]=
{ B00000000,
  B00111110,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
},
smile_bmp[] =
{ B00111100,
B01000010,
B10100101,
B10000001,
B10100101,
B10011001,
B01000010,
B00111100 },
neutral_bmp[] =
{ B00111100,
B01000010,
B10100101,
B10000001,
B10111101,
B10000001,
B01000010,
B00111100 },
frown_bmp[] =
{ B00111100,
B01000010,
B10100101,
B10000001,
B10011001,
B10100101,
B01000010,
B00111100 };