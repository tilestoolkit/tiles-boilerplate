#include "BLE_Handler.h"

BLE_Handler::BLE_Handler()
{
    Connected = false;
    String MAC = String(*(uint8_t *)0x100000a4, HEX);
    String suffix = SUFFIX;
    AdvertiseName = suffix + MAC;    
}

// Code that executes everytime token is being connected to
void RFduinoBLE_onConnect()
{
    extern BLE_Handler BLE;
    BLE.Connected = true;
    Serial.println("Connection established");
}

// Code that executes everytime token is being disconnected from
void RFduinoBLE_onDisconnect()
{
    extern BLE_Handler BLE;
    BLE.Connected = false;
    Serial.println("Disconnected from device");    
}

//Add a token to the stack
void BLE_Handler::Emit(Token *Event)
{
    if(Event != NULL)
    {
    //  Serial.println("Added Event to stack");
      ReceivedStack.push(Event);  
    }
}

//Send a token via BT
void BLE_Handler::SendEvent(Token* Event)
{
    String payload = Event->getEventString();
    char sendData[20] = {0};
    payload.toCharArray(sendData, payload.length()+1);    
    RFduinoBLE.send(sendData, payload.length());
    Serial.print("**Event sent: "); Serial.print(payload); Serial.println("**");
}

// BT Token Received Callback
void RFduinoBLE_onReceive(char *data, int length)
{
    extern BLE_Handler BLE;
    BLE.ReceiveEvent(data, length);
   // Serial.print("Payload received: "); Serial.println(data);
}

// Add a token to the stack
void BLE_Handler::ReceiveEvent(char *Data, int Lenght)
{ 
    Token *NewEvent = new Token(Data, Lenght);
    ReceivedStack.push(NewEvent);
}

// Token handling loop
void BLE_Handler::ProcessEvents()
{
    extern Feedbacks_Handler feedback_handle;
    
    if(ReceivedStack.count() == 0)
      return;
      
    Token *Command = NULL;
    Command = ReceivedStack.pop();

    if(Command == NULL)
      return;
    else
        {
            String temp = Command->getEventString();
            Serial.print("**Command received: "); Serial.print(temp); Serial.println("**");
        }   
    if(Command->FirstValue == String("led"))
    {
        if(Command->SecondValue == String("on"))
        {
          feedback_handle.setColor(Command->ThirdValue);
        }
        else if(Command->SecondValue == String("blink"))
        {
          feedback_handle.blink(Command->ThirdValue);
        }    
        else if(Command->SecondValue == String("fade"))
        {
          feedback_handle.fade(Command->ThirdValue);
        }
        else if(Command->SecondValue == String("off"))
        {
          feedback_handle.setColor(Command->SecondValue);
        }

    }
    else if(Command->FirstValue == String("haptic"))
    {
        feedback_handle.Vibrate(Command->SecondValue);
    }
    else if(Command->FirstValue == String("matrix"))
    {
        if(Command->SecondValue == String("gazing")){
        feedback_handle.startGazing();
        } else if(Command->SecondValue == String("off")){
            feedback_handle.stopGazing();
        }  else {
            feedback_handle.showFace(String(Command->SecondValue));
        }
    }
    else
        Serial.println("**COMMAND NOT RECOGNIZED**");
}

/*********************************TOKEN CLASS************************************************/

Token::Token()
{
}

Token::Token(char* Data, uint8_t Length)
{
    String Command;
    Command = Data;
    Command = Command.substring(0, Length);
    
    int CommaIndex = Command.indexOf(',');
    if(CommaIndex > 0)
    {
    int SecondCommaIndex = Command.indexOf(',', CommaIndex + 1);
    FirstValue = Command.substring(0, CommaIndex);
    SecondValue = Command.substring(CommaIndex + 1, SecondCommaIndex);
    ThirdValue = "";
    if(SecondCommaIndex > 0)
    {
      ThirdValue = Command.substring(SecondCommaIndex + 1);
    }
    }
    else
    {
        FirstValue = Command.substring(0, CommaIndex);
        SecondValue = "";
        ThirdValue = "";        
    }    
}

Token::Token(String Data)
{
    String Command;
    Command = Data;
    
    
    int CommaIndex = Command.indexOf(',');
    if(CommaIndex > 0)
    {
    int SecondCommaIndex = Command.indexOf(',', CommaIndex + 1);
    FirstValue = Command.substring(0, CommaIndex);
    SecondValue = Command.substring(CommaIndex + 1, SecondCommaIndex);
    ThirdValue = "";
    if(SecondCommaIndex > 0)
    {
      ThirdValue = Command.substring(SecondCommaIndex + 1);
    }
    }
    else
    {
        FirstValue = Command.substring(0, CommaIndex);
        SecondValue = "";
        ThirdValue = "";        
    }    
}


String Token::getEventString()
{
    char sendData[20] = {0};
    String Payload;
    extern BLE_Handler BLE;
    
    Payload = BLE.AdvertiseName + "," + FirstValue;
    
    if(SecondValue.length() != 0)
    {
      Payload = Payload + "," + SecondValue;

      if(ThirdValue.length() != 0)
        Payload = Payload + "," + ThirdValue;
    }

    return Payload;
}

void Token::set(char* Data, uint8_t Length)
{
    String Command;
    Command = Data;
    Command = Command.substring(0, Length);
  
    int CommaIndex = Command.indexOf(',');
    //  Search for the next comma just after the first
    int SecondCommaIndex = Command.indexOf(',', CommaIndex + 1);
  
    FirstValue = Command.substring(0, CommaIndex);
    SecondValue = Command.substring(CommaIndex + 1, SecondCommaIndex);
    ThirdValue = Command.substring(SecondCommaIndex + 1);
}

void Token::set(String pFirstValue, String pSecondValue, String pThirdValue)
{
    FirstValue = pFirstValue;
    SecondValue = pSecondValue;
    ThirdValue = pThirdValue;
}

