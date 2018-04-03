#include "Temp_Si7051.h"

Temp_Si7051::Temp_Si7051(){
    
    // Initialize temperature sensor
    si7051.begin(0x40);

    Serial.println("Si7051 available");
    SensorAvailable = true;
}

float Temp_Si7051::read(){
    return si7051.readT();
}