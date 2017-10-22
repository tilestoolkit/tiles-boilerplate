# 1 "/Users/simone/Desktop/Tiles/tiles-bolierplate/boilerplate/boilerplate.ino"
# 1 "/Users/simone/Desktop/Tiles/tiles-bolierplate/boilerplate/boilerplate.ino"
/********************************************************
  # NAME: boilerplate.ino
  # AUTHOR: Simone Mora (simonem@ntnu.no)
  # DATE: --
  # LICENSE: Apache V2.0
********************************************************/

# 9 "/Users/simone/Desktop/Tiles/tiles-bolierplate/boilerplate/boilerplate.ino" 2
# 10 "/Users/simone/Desktop/Tiles/tiles-bolierplate/boilerplate/boilerplate.ino" 2
# 11 "/Users/simone/Desktop/Tiles/tiles-bolierplate/boilerplate/boilerplate.ino" 2
# 12 "/Users/simone/Desktop/Tiles/tiles-bolierplate/boilerplate/boilerplate.ino" 2
# 13 "/Users/simone/Desktop/Tiles/tiles-bolierplate/boilerplate/boilerplate.ino" 2

# 15 "/Users/simone/Desktop/Tiles/tiles-bolierplate/boilerplate/boilerplate.ino" 2


# 18 "/Users/simone/Desktop/Tiles/tiles-bolierplate/boilerplate/boilerplate.ino" 2

//Variables for timing
uint_fast16_t volatile number_of_ms = 10;

// Variables for BLE
BLE_Handler BLE;

// Variables for Sensors
Sensors_Handler sensor_handle(&BLE);
ADXL345 *ACCELEROMETER = 
# 27 "/Users/simone/Desktop/Tiles/tiles-bolierplate/boilerplate/boilerplate.ino" 3 4
                        __null
# 27 "/Users/simone/Desktop/Tiles/tiles-bolierplate/boilerplate/boilerplate.ino"
                            ;
LSM9DS0 *IMU = 
# 28 "/Users/simone/Desktop/Tiles/tiles-bolierplate/boilerplate/boilerplate.ino" 3 4
              __null
# 28 "/Users/simone/Desktop/Tiles/tiles-bolierplate/boilerplate/boilerplate.ino"
                  ;
CAP1188 *TOUCH = 
# 29 "/Users/simone/Desktop/Tiles/tiles-bolierplate/boilerplate/boilerplate.ino" 3 4
                __null
# 29 "/Users/simone/Desktop/Tiles/tiles-bolierplate/boilerplate/boilerplate.ino"
                    ;

// Variables for Feedbacks 
Feedbacks_Handler feedback_handle;
Haptic *HapticMotor;
DRV2605 *HapticIC;
RGB_LED *LED;
NEO_STRIP *STRIP = 
# 36 "/Users/simone/Desktop/Tiles/tiles-bolierplate/boilerplate/boilerplate.ino" 3 4
                  __null
# 36 "/Users/simone/Desktop/Tiles/tiles-bolierplate/boilerplate/boilerplate.ino"
                      ;
MATRIX *M_MATRIX = 
# 37 "/Users/simone/Desktop/Tiles/tiles-bolierplate/boilerplate/boilerplate.ino" 3 4
                  __null
# 37 "/Users/simone/Desktop/Tiles/tiles-bolierplate/boilerplate/boilerplate.ino"
                      ;
//STATUS_LED status_led;
BUZZER buzz;


int ledState = (0x1);
int buttonState = (0x0);
int lastButtonState = (0x0);
int i = 0;
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 1000; // the debounce time; increase if the output flickers

void setup(void)
{


    if(!false){
        Serial.begin(9600);
    }
    __enable_irq();

    Serial.println("START SETUP");

    //status_led = new STATUS_LED();
    //status_led.on(); 

    //Configure pushbutton to wake up the device
    pinMode(16, (0x0));
    digitalWrite(16,(0x1));

    //Initialization of SENSORS
    //Accelerometer
    if(true){
    ACCELEROMETER = new ADXL345(28);
    sensor_handle.setAccelerometer(ACCELEROMETER);
    }
    //IMU
    if(false){
    IMU = new LSM9DS0();
    sensor_handle.setInertialCentral(IMU);
    }
    //Touch 
    if(false){
    TOUCH = new CAP1188(0);
    sensor_handle.setTouchSensor(TOUCH);
    }
    //Intitialization of FEEDBACKS
    //DotMatrix
    if(false){
    M_MATRIX = new MATRIX(0);
    feedback_handle.setMATRIX(M_MATRIX);
    }
    //HapticMotor (Analog)
    if(false){
    HapticMotor = new Haptic(3);
    feedback_handle.setHapticMotor(HapticMotor);
    }
    //HapticMotor (Analog)
    if(true){
    HapticIC = new DRV2605();
    feedback_handle.setHapticMotor(HapticIC);
    }
    //RGB LED
    if(false){
    LED = new RGB_LED(0, 1, 2);
    feedback_handle.setRGB_LED(LED);
    }
    //NeoPixels LED/STRIP
    if(false){
    STRIP = new NEO_STRIP();
    feedback_handle.setNEO_STRIP(STRIP);
    //feedback_handle.setColor("blue");
    //delay(500);
    //feedback_handle.setColor("off");
    }

    Serial.println("**Setup Complete0**");
    BLE.start();
    timer_config(1000);
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


/*******************INTERNAL FUNCTIONS********************/

void timer_config(unsigned int ms)
{
  Serial.println("Configuring timer");
    ((NRF_TIMER_Type *) 0x40009000UL)->TASKS_STOP = 1; // Stop timer
    ((NRF_TIMER_Type *) 0x40009000UL)->MODE = (0UL) /*!< Select Timer mode */; // sets the timer to TIME mode (doesn't make sense but OK!)
    ((NRF_TIMER_Type *) 0x40009000UL)->BITMODE = (0UL) /*!< 16 bit timer bit width */; // with BLE only Timer 1 and Timer 2 and that too only in 16bit mode
    ((NRF_TIMER_Type *) 0x40009000UL)->PRESCALER = 9; // Prescaler 9 produces 31250 Hz timer frequency => t = 1/f =>  32 uS
                                                                     // The figure 31250 Hz is generated by the formula (16M) / (2^n)
                                                                     // where n is the prescaler value
                                                                     // hence (16M)/(2^9)=31250
    ((NRF_TIMER_Type *) 0x40009000UL)->TASKS_CLEAR = 1; // Clear timer

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //        Conversion to make cycle calculation easy
    //        Since the cycle is 32 uS hence to generate cycles in mS we need 1000 uS
    //        1000/32 = 31.25  Hence we need a multiplication factor of 31.25 to the required cycle time to achive it
    //        e.g to get a delay of 10 mS      we would do
    //        NRF_TIMER2->CC[0] = (10*31)+(10/4);
    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    ((NRF_TIMER_Type *) 0x40009000UL)->CC[0] = (number_of_ms * 31) + (number_of_ms / 4); // CC[0] register holds interval count value i.e your desired cycle
    ((NRF_TIMER_Type *) 0x40009000UL)->INTENSET = (1UL) /*!< Read: Enabled */ << (16UL) /*!< Position of COMPARE0 field. */; // Enable COMAPRE0 Interrupt
    ((NRF_TIMER_Type *) 0x40009000UL)->SHORTS = ((1UL) /*!< Enable shortcut */ << (0UL) /*!< Position of COMPARE0_CLEAR field. */); // Count then Complete mode enabled
    attachInterrupt(TIMER1_IRQn, TIMER1_Interrupt, 4); // also used in variant.cpp in the RFduino2.2 folder to configure the RTC1
    ((NRF_TIMER_Type *) 0x40009000UL)->TASKS_START = 1; // Start TIMER
    Serial.println("Timer configured");
  }

void TIMER1_Interrupt(void)
{
    if (((NRF_TIMER_Type *) 0x40009000UL)->EVENTS_COMPARE[0] != 0)
    {
        //Serial.println("TIMER UPDATED");
        sensor_handle.HandleTime(number_of_ms);
        feedback_handle.HandleTime(number_of_ms);
       // status_led.HandleTime(number_of_ms);
        ((NRF_TIMER_Type *) 0x40009000UL)->EVENTS_COMPARE[0] = 0;
    }
}
