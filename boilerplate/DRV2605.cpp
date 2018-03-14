#include "DRV2605.h"

DRV2605::DRV2605(){
    drv.begin();
    drv.selectLibrary(1);
    // I2C trigger by sending 'go' command 
    // default, internal trigger when sending GO command
    drv.setMode(DRV2605_MODE_INTTRIG); 
}

void DRV2605::Vibrate(uint8_t pattern){
  // set the effect to play
  drv.setWaveform(0, pattern);  // play effect 
  drv.setWaveform(1, 0);       // end waveform
  // play the effect!
  drv.go();
}

void DRV2605::burst(){
  // set the effect to play
  drv.setWaveform(0, 14);  // play effect
  delay(1,100);
  drv.setWaveform(2, 14);  // play effect
  delay(3,100);
  drv.setWaveform(4, 14);  // play effect
  delay(5,100);
  drv.setWaveform(6, 14);  // play effect
  
  drv.setWaveform(7, 0);       // end waveform
  // play the effect!
  drv.go();
}

void DRV2605::shortv(){
  // set the effect to play
  drv.setWaveform(0, SHORT_ALERT);  // play effect
  drv.setWaveform(1, 0);       // end waveform
  // play the effect!
  drv.go();
}

void DRV2605::longv(){
  // set the effect to play
  drv.setWaveform(0, SMOOTH_HUM);  // play effect
  drv.setWaveform(1, SMOOTH_HUM);  // play effect
  drv.setWaveform(2, SMOOTH_HUM);  // play effect
  drv.setWaveform(3, SMOOTH_HUM);  // play effect
  drv.setWaveform(4, 0);       // end waveform
  // play the effect!
  drv.go();
}

void DRV2605::raise(){
  // set the effect to play
  drv.setWaveform(0, TRANS_RAMP_UP);  // play effect
  drv.setWaveform(1, 0);       // end waveform
  // play the effect!
  drv.go();
}

void DRV2605::fall(){
  // set the effect to play
  drv.setWaveform(0, TRANS_RAMP_DOWN_50);  // play effect
  drv.setWaveform(1, 0);       // end waveform
  // play the effect!
  drv.go();
}

void DRV2605::raiseFall(){
  // set the effect to play
  drv.setWaveform(0, TRANS_RAMP_UP);  // play effect
  drv.setWaveform(1, TRANS_RAMP_DOWN_50);  // play effect
  drv.setWaveform(2, 0);       // end waveform
  // play the effect!
  drv.go();
}

void DRV2605::delay(uint8_t step, uint8_t ms){
  drv.setWaveform(step, (0x80 | (ms/10)));  // set bit 7 high to enable waiting, bits 6-0 indicate waiting time (cs)
}