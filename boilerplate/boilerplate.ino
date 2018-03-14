/********************************************************
  # NAME: boilerplate.ino
  # AUTHOR: Simone Mora (simonem@ntnu.no), Francesco Gianni (francg@idi.ntnu.no)
  # DATE: --
  # LICENSE: Apache V2.0
********************************************************/

#include <Wire.h>
#include <WInterrupts.h>
#include <bluefruit.h>
#include <string.h>
#include "BLE_Handler.h"
#include "Feedbacks_Handler.h"
#include "Sensors_Handler.h"
#include "CONFIG.h"
#include "STATUS_LED.h"

// Variables for BLE
BLE_Handler BLE;

//Variables for timing
SoftwareTimer timer;
uint_fast16_t volatile number_of_ms = 10;

// Variables for Sensors
Sensors_Handler sensor_handle(&BLE);
ADXL345 *ACCELEROMETER = NULL;
LSM9DS0 *IMU = NULL;
CAP1188 *TOUCH = NULL;
Temp_Si7051 *TEMP = NULL;
Hum_HDC2010 *HUM = NULL;
OFF_Pin *OFF = NULL;

// Variables for Feedbacks 
Feedbacks_Handler feedback_handle;
Haptic *HapticMotor;
DRV2605 *HapticIC;
RGB_LED *LED;
NEO_STRIP *STRIP = NULL;
MATRIX *M_MATRIX = NULL;
//STATUS_LED status_led;
BUZZER *Buzzer;


int ledState = HIGH;         
int buttonState = LOW;             
int lastButtonState = LOW;  
int i = 0; 
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 1000;    // the debounce time; increase if the output flickers

void setup(void)
{
   
    Serial.begin(9600);      
    interrupts(); 

    Serial.println("START SETUP");

    //Configure status led   
    //status_led = new STATUS_LED();
    //status_led.on(); 
    
    //Configure pushbutton to wake up the device
    pinMode(BUTTON_PIN, INPUT);
    digitalWrite(BUTTON_PIN,HIGH);

    //Initialization of SENSORS
    //Accelerometer
    if(xAccelerometer_ADXL345){
    ACCELEROMETER = new ADXL345();
    sensor_handle.setAccelerometer(ACCELEROMETER);
    }
    //IMU
    if(xIMU_LSM9DS0){
    IMU = new LSM9DS0();
    sensor_handle.setInertialCentral(IMU);
    }
    //Touch 
    if(xTouch_CAP1188){
    TOUCH = new CAP1188(0);
    sensor_handle.setTouchSensor(TOUCH);
    }
    //Temp
    if(xTemp_Si7051){
    TEMP = new Temp_Si7051();
    sensor_handle.setTempSensor(TEMP);
    }
    //Hum
    if(xHum_HDC2010){
    HUM = new Hum_HDC2010();
    sensor_handle.setHumSensor(HUM);
    }
    //Off pin
    if(xOFF_PIN){
    OFF = new OFF_Pin();
    sensor_handle.setOffPin(OFF);
    }

    //Intitialization of FEEDBACKS
    //DotMatrix
    if(xDOTM_MATRIX){
    M_MATRIX = new MATRIX(0);
    feedback_handle.setMATRIX(M_MATRIX);
    }
    //HapticMotor (Analog)
    if(xHAPTIC_analog){
    HapticMotor = new Haptic(VIBRATING_M_PIN);
    feedback_handle.setHapticMotor(HapticMotor);
    }
    //HapticMotor (Analog)
    if(xHAPTIC_IC){
    HapticIC = new DRV2605();
    feedback_handle.setHapticMotor(HapticIC);
    }
    //RGB LED
    if(xLED_RGB){
    LED = new RGB_LED(PIN_LED_RED, PIN_LED_GREEN, PIN_LED_BLUE);
    feedback_handle.setRGB_LED(LED);
    }  
    //NeoPixels LED/STRIP
    if(xLED_NEO){
    STRIP = new NEO_STRIP();
    feedback_handle.setNEO_STRIP(STRIP);
    //feedback_handle.setColor("blue");
    //delay(500);
    //feedback_handle.setColor("off");
    }
    //Buzzer
    if(xBUZZER){
    Buzzer = new BUZZER();
    feedback_handle.setBuzzer(Buzzer);
    }

    //Start timers
    timer.begin(10, timer_callback);
    timer.start();

    //Start BT stack
    BLE.start();
    Serial.println("**Setup Complete**");  
}

void loop(void)
{   
  
    //int readingA = digitalRead(16);
    //Serial.print("READING: "); Serial.println(readingA);
  /*
    if (readingA != lastButtonState) {
      // reset the debouncing timer
      //Serial.print("Button PRESSED: "); Serial.println(readingA);
      lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {    
      if (readingA != buttonState) {
        buttonState = readingA;
        if(buttonState == LOW){
          Serial.print("DEBUG: "); Serial.println(i);
          i++;
          delay(100);
          //BLE.shoutdown();
        }
      }
    }
    lastButtonState = readingA;
    */

    //Enable serial input of commands
    while(Serial.available()){
    String serialCommand = Serial.readString();
    serialCommand.trim();
    Token *command = new Token(serialCommand);
    BLE.ReceivedStack.push(command);
    }

    //Refresh values
   // status_led.RefreshValues();
    sensor_handle.pollEvent();
    feedback_handle.UpdateFeedback();
    BLE.ProcessEvents();
    delay(10); // 10ms Important delay, do not delete it
}

void timer_callback(TimerHandle_t xTimerID)
{
  (void) xTimerID;
  sensor_handle.HandleTime(number_of_ms);
  feedback_handle.HandleTime(number_of_ms);
  //status_led.HandleTime(number_of_ms);
  
}

