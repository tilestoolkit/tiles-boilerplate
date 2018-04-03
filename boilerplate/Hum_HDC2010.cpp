#include "Hum_HDC2010.h"


Hum_HDC2010::Hum_HDC2010(){
    
    temperature = 0;
    humidity = 0;
    // Initialize temperature sensor
    hdc2010.begin();
    hdc2010.reset();

    hdc2010.setMeasurementMode(HUMID_ONLY); // # HUMID_ONLY // # TEMP_AND_HUMID
    // hdc2010.enableHeater();
    // delay(10000);
    // hdc2010.disableHeater();
    hdc2010.triggerMeasurement();

    Serial.println("HDC2010 available");
    SensorAvailable = true;
}

String Hum_HDC2010::read(){
    hdc2010.triggerMeasurement();
    // temperature = hdc2010.readTemp();
    humidity = hdc2010.readHumidity();
    // return String(humidity);
    return String(humidity);
}