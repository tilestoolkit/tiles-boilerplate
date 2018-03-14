#ifndef Haptic_h
#define Haptic_h

#include <Arduino.h>

#define ACTIVE true
#define INACTIVE false

class Haptic
{
    public:
    		Haptic(int pin_vibrating_motor);
    		void Vibrate(int ms);
    		void VibrateShort();
    		void VibrateLong();

        void RefreshValues();
        void HandleTime(unsigned int ElapsedTime);
		
	  private:
        void StartVibrate();
        void StopVibrate();
        
        unsigned int  Haptic_Timing;
        unsigned int  VibrateTime;
        bool State;
		    int _HapticPin;
		
};

#endif
