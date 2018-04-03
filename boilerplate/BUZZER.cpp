#include "BUZZER.h"

BUZZER::BUZZER()
{
    //Constructor code
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite( BUZZER_PIN, LOW);
}

void BUZZER::play_tune(String note) {
}

void BUZZER::play_melody(char *song) {
    play_rtttl(song);
    digitalWrite(BUZZER_PIN, LOW);
}

void BUZZER::tone (int frequency, int duration) {
    
    uint32_t start = millis();
    uint32_t stop = start + duration;
    int halfCycle = 1000 / ( 2 * frequency );
    for ( int i=1 ; millis() < stop ; i++ ) {
        digitalWrite( BUZZER_PIN, ! digitalRead( BUZZER_PIN ) );
        while ( millis() < ( start + ( i * halfCycle ))) {}
    }
}


void BUZZER::play_rtttl(char *p)
{
  // Absolutely no error checking in here

  byte default_dur = 4;
  byte default_oct = 6;
  int bpm = 63;
  int num;
  long wholenote;
  long duration;
  byte note;
  byte scale;

  // format: d=N,o=N,b=NNN:
  // find the start (skip name, etc)

  while(*p != ':') p++;    // ignore name
  p++;                     // skip ':'

  // get default duration
  if(*p == 'd') {
    p++; p++;              // skip "d="
    num = 0;
    while(isdigit(*p)) {
      num = (num * 10) + (*p++ - '0');
    }
    if(num > 0) default_dur = num;
    p++;                   // skip comma
  }

  Serial.print("ddur: "); Serial.println(default_dur, 10);

  // get default octave
  if(*p == 'o') {
    p++; p++;              // skip "o="
    num = *p++ - '0';
    if(num >= 3 && num <=7) default_oct = num;
    p++;                   // skip comma
  }

  Serial.print("doct: "); Serial.println(default_oct, 10);

  // get BPM
  if(*p == 'b') {
    p++; p++;              // skip "b="
    num = 0;
    while(isdigit(*p)) {
      num = (num * 10) + (*p++ - '0');
    }
    bpm = num;
    p++;                   // skip colon
  }

  Serial.print("bpm: "); Serial.println(bpm, 10);

  // BPM usually expresses the number of quarter notes per minute
  wholenote = (60 * 1000L / bpm) * 4;  // this is the time for whole note (in milliseconds)

  Serial.print("wn: "); Serial.println(wholenote, 10);


  // now begin note loop
  while(*p) {
    // first, get note duration, if available
    num = 0;
    while(isdigit(*p)) {
      num = (num * 10) + (*p++ - '0');
    }
    
    if(num) duration = wholenote / num;
    else duration = wholenote / default_dur;  // we will need to check if we are a dotted note after

    // now get the note
    note = 0;

    switch(*p) {
      case 'c':
        note = 1;
        break;
      case 'd':
        note = 3;
        break;
      case 'e':
        note = 5;
        break;
      case 'f':
        note = 6;
        break;
      case 'g':
        note = 8;
        break;
      case 'a':
        note = 10;
        break;
      case 'b':
        note = 12;
        break;
      case 'p':
      default:
        note = 0;
    }
    p++;

    // now, get optional '#' sharp
    if(*p == '#') {
      note++;
      p++;
    }

    // now, get optional '.' dotted note
    if(*p == '.') {
      duration += duration/2;
      p++;
    }
  
    // now, get scale
    if(isdigit(*p)) {
      scale = *p - '0';
      p++;
    }
    else {
      scale = default_oct;
    }

    scale += OCTAVE_OFFSET;

    if(*p == ',')
      p++;       // skip comma for next note (or we may be at the end)

    // now play the note

    if(note) {
      Serial.print("Playing: ");
      Serial.print(scale, 10); Serial.print(' ');
      Serial.print(note, 10); Serial.print(" (");
      Serial.print(notes[(scale - 4) * 12 + note], 10);
      Serial.print(") ");
      Serial.println(duration, 10);
      tone(notes[(scale - 4) * 12 + note], duration);
    //   delay(duration);
    //   tone1.stop();
    }
    else {
      Serial.print("Pausing: ");
      Serial.println(duration, 10);
      delay(duration);
    }
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