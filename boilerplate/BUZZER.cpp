#include "BUZZER.h"

BUZZER::BUZZER()
{
    //Constructor code
    pinMode(BUZZER_PIN, OUTPUT);
}

void BUZZER::play_tune(String note){

}

void BUZZER::play_melody(){
    for (int thisNote = 0; thisNote < 8; thisNote++) {
        
            // to calculate the note duration, take one second divided by the note type.
            //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
            int noteDuration = 1000 / noteDurations[thisNote];
            tone(BUZZER_PIN, melody[thisNote], noteDuration);
        
            // to distinguish the notes, set a minimum time between them.
            // the note's duration + 30% seems to work well:
            int pauseBetweenNotes = noteDuration * 1.30;
            delay(pauseBetweenNotes);
            // stop the tone playing:
            //noTone(4);
          }
}

void BUZZER::tone ( int pin, int frequency, int duration ) {
    uint32_t start = millis();
    uint32_t stop = start + ( duration * 1000 );
    int halfCycle = 1000 / ( 2 * frequency );
    
    for ( int i=1 ; millis() < stop ; i++ ) {
        digitalWrite( pin, ! digitalRead( pin ) );
        while ( millis() < ( start + ( i * halfCycle ))) {}
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