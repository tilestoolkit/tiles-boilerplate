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