#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "faces.h"

#define BLINKING true
#define NO_BLINKING false

class MATRIX
{
    public: 
        MATRIX(int i);
        void start_gazing();
        void stop_gazing();

        void gazing();

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
        
        #define REFRESH_RATE 10 //half frequence because of the 10ms delay in the loop

};