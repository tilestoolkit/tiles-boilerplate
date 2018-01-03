#include "BUZZER.h"

BUZZER::BUZZER()
{
    //Constructor code
    
}

void BUZZER::play_tune(String note){

}

void BUZZER::play_melody(){
    for (int thisNote = 0; thisNote < 8; thisNote++) {
        
            // to calculate the note duration, take one second divided by the note type.
            //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
            int noteDuration = 1000 / noteDurations[thisNote];
            //tone(4, melody[thisNote], noteDuration);
        
            // to distinguish the notes, set a minimum time between them.
            // the note's duration + 30% seems to work well:
            int pauseBetweenNotes = noteDuration * 1.30;
            delay(pauseBetweenNotes);
            // stop the tone playing:
            //noTone(4);
          }
}

void BUZZER::HandleTime(unsigned int  ElapsedTime)
{
    Buzzer_Timing += ElapsedTime;
}

void BUZZER::RefreshValues()
{
    if(Buzzer_Timing > RefreshThreshold)
    {

      Buzzer_Timing = 0;
    }

}