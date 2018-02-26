#ifndef BLEHANDLER_h
#define BLEHANDLER_h

#include <bluefruit.h>
#include <StackArray.h>
#include "CONFIG.h"
#include "Feedbacks_Handler.h"
#include "STATUS_LED.h"

typedef volatile uint32_t REG32;
#define pREG32 (REG32 *)
#define MAC_ADDRESS_LOW   (*(pREG32 (0x100000a4)))

class Token;

class BLE_Handler
{
    public:
      BLE_Handler(); //  Default constructor
      void Transmit();
      void SendEvent(Token* Event);    
      void ReceiveEvent(char *Data, int Lenght);
      void ProcessEvents();
      void Emit(Token *Event);
      void shoutdown();
      void start();

      bool Connected;
      bool EventReceived;   // true if an event has been Received, cleared with a call to ProcessEvents()
      bool EventToSend;     // true if there are events waiting to be send
      String AdvertiseName;          
      StackArray<Token*> ReceivedStack;   
      StackArray<Token*> SendStack;
      
    
      char DeviceName[8] = {0};

      BLEService        service = BLEService(0x1234);
      BLECharacteristic char1 = BLECharacteristic(0xAA01);
      BLECharacteristic char2 = BLECharacteristic(0xAA02);
      BLECharacteristic char3 = BLECharacteristic(0xAA03);
      static void connect_callback(uint16_t conn_handle);
      static void disconnect_callback(uint16_t conn_handle, uint8_t reason);
      static void write_callback(BLECharacteristic& chr, uint8_t* data, uint16_t len, uint16_t offset);

};

class Token
{
  public:
    Token();
    Token(char* Data, uint8_t Length);
    Token(String Data);
    String getEventString();
    void set(char* Data, uint8_t Length);
    void set(String pFirstValue, String pSecondValue = String(""), String pThirdValue = String(""));  
    String FirstValue;
    String SecondValue;
    String ThirdValue;

    
};

#endif
