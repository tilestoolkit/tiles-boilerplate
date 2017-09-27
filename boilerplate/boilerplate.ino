/********************************************************
  # NAME: boilerplate.ino
  # AUTHOR: Simone Mora (simonem@ntnu.no)
  # DATE: --
  # LICENSE: Apache V2.0
********************************************************/

#include <Wire.h>
#include <WInterrupts.h>
#include <RFduinoBLE.h>
#include <string.h>
#include "BLE_Handler.h"
#include "Feedbacks_Handler.h"
#include "Sensors_Handler.h"
#include "CONFIG.h"

//Variables for timing
uint_fast16_t volatile number_of_ms = 10;    

// Variables for BLE
BLE_Handler BLE;

// Variables for Sensors
Sensors_Handler sensor_handle(&BLE);
ADXL345 *ACCELEROMETER = NULL;
LSM9DS0 *IMU = NULL;
CAP1188 *TOUCH = NULL;

// Variables for Feedbacks 
Feedbacks_Handler feedback_handle;
Haptic *HapticMotor;
DRV2605 *HapticIC;
RGB_LED *LED;
NEO_STRIP *STRIP = NULL;
MATRIX *M_MATRIX = NULL;


void setup(void)
{
    override_uart_limit = true;  
    if(!xLED_RGB){
        Serial.begin(9600);
    }        
    interrupts(); 

    //Initialization of SENSORS
    //Accelerometer
    if(xAccelerometer_ADXL345){
    ACCELEROMETER = new ADXL345(ACC_INT1_PIN);
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
    LED = new RGB_LED(0, 1, 2);
    feedback_handle.setRGB_LED(LED);
    }  
    //NeoPixels LED/STRIP
    if(xLED_NEO){
    STRIP = new NEO_STRIP();
    feedback_handle.setNEO_STRIP(STRIP);
    feedback_handle.setColor("blue");
    delay(500);
    feedback_handle.setColor("off");
    }

    // Configure the RFduino BLE properties
    char DeviceName[8] = {0};
    BLE.AdvertiseName.toCharArray(DeviceName, 8);  
    RFduinoBLE.deviceName = DeviceName;
    RFduinoBLE.txPowerLevel = -20;

    // Start the BLE stack
    RFduinoBLE.begin();
    Serial.println("**Setup Completed**");  
    timer_config();
}

void loop(void)
{   
    while(Serial.available()){
    String serialCommand = Serial.readString();
    //Serial.print("SERIAL EVENT: "); Serial.println(serialCommand);
    Token *command = new Token(serialCommand);
    BLE.ReceivedStack.push(command);
    }

    sensor_handle.pollEvent();
    feedback_handle.UpdateFeedback();
    BLE.ProcessEvents();
    delay(10); // 10ms Important delay, do not delete it
}


/*******************INTERNAL FUNCTIONS********************/


#define TRIGGER_INTERVAL 1000      // ms
void timer_config(void)
{
    NRF_TIMER1->TASKS_STOP = 1;                                      // Stop timer
    NRF_TIMER1->MODE = TIMER_MODE_MODE_Timer;                        // sets the timer to TIME mode (doesn't make sense but OK!)
    NRF_TIMER1->BITMODE = TIMER_BITMODE_BITMODE_16Bit;               // with BLE only Timer 1 and Timer 2 and that too only in 16bit mode
    NRF_TIMER1->PRESCALER = 9;                                       // Prescaler 9 produces 31250 Hz timer frequency => t = 1/f =>  32 uS
                                                                     // The figure 31250 Hz is generated by the formula (16M) / (2^n)
                                                                     // where n is the prescaler value
                                                                     // hence (16M)/(2^9)=31250
    NRF_TIMER1->TASKS_CLEAR = 1;                                     // Clear timer
   
    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //        Conversion to make cycle calculation easy
    //        Since the cycle is 32 uS hence to generate cycles in mS we need 1000 uS
    //        1000/32 = 31.25  Hence we need a multiplication factor of 31.25 to the required cycle time to achive it
    //        e.g to get a delay of 10 mS      we would do
    //        NRF_TIMER2->CC[0] = (10*31)+(10/4);
    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   
    NRF_TIMER1->CC[0] = (number_of_ms * 31) + (number_of_ms / 4);                                                              // CC[0] register holds interval count value i.e your desired cycle
    NRF_TIMER1->INTENSET = TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos;                                     // Enable COMAPRE0 Interrupt
    NRF_TIMER1->SHORTS = (TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos);                             // Count then Complete mode enabled
    attachInterrupt(TIMER1_IRQn, TIMER1_Interrupt);                                                                            // also used in variant.cpp in the RFduino2.2 folder to configure the RTC1
    NRF_TIMER1->TASKS_START = 1;                                                                                               // Start TIMER
}

void TIMER1_Interrupt(void)
{
    if (NRF_TIMER1->EVENTS_COMPARE[0] != 0)
    {        
        sensor_handle.HandleTime(number_of_ms);
        feedback_handle.HandleTime(number_of_ms);
        NRF_TIMER1->EVENTS_COMPARE[0] = 0;
    }
}