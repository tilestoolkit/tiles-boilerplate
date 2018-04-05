#include "BLE_Handler.h"

BLE_Handler::BLE_Handler()
{
    Connected = false;   
}

void BLE_Handler::start()
{
    Bluefruit.begin();
    uint32_t addr_low  = MAC_ADDRESS_LOW;
    String MAC = String((addr_low) & 0xFF, HEX);
    AdvertiseName = String(SUFFIX + MAC);
    Bluefruit.setName(AdvertiseName.c_str());
    Bluefruit.setConnectCallback(connect_callback);
    Bluefruit.setDisconnectCallback(disconnect_callback);
    service.begin();
    
    char1.setProperties(CHR_PROPS_READ | CHR_PROPS_NOTIFY);
    char1.setPermission(SECMODE_OPEN, SECMODE_NO_ACCESS);
    char1.setMaxLen(20);
    //char1.setCccdWriteCallback(cccd_callback);  // Optionally capture CCCD updates
    char1.begin();

    char2.setProperties(CHR_PROPS_WRITE | CHR_PROPS_WRITE_WO_RESP);
    char2.setPermission(SECMODE_OPEN, SECMODE_NO_ACCESS);
    char2.setFixedLen(1);
    char2.write8(2);    // Set the characteristic to 'Wrist' (2)
    char2.begin();
    
    char3.setProperties(CHR_PROPS_WRITE | CHR_PROPS_WRITE_WO_RESP);
    char2.setPermission(SECMODE_OPEN, SECMODE_NO_ACCESS);
    char3.setWriteCallback(write_callback);  
    char3.setMaxLen(18);
    char3.begin();
    // Advertising packet
    Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
    Bluefruit.Advertising.addTxPower();
    // Include HRM Service UUID
    Bluefruit.Advertising.addService(service);
    // Include Name
    Bluefruit.Advertising.addName();
    Bluefruit.Advertising.restartOnDisconnect(true);
    Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
    Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
    Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds 
    Serial.println("BLE STARTED"); 
}

void BLE_Handler::connect_callback(uint16_t conn_handle)
{
  char central_name[32] = { 0 };
  Bluefruit.Gap.getPeerName(conn_handle, central_name, sizeof(central_name));
  Serial.print("Connected to ");
  Serial.println(central_name);
  extern BLE_Handler BLE;
  BLE.Connected = true;
}

void BLE_Handler::disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;
  extern BLE_Handler BLE;
  BLE.Connected = false;
  Serial.println("Disconnected from device"); 
}

void BLE_Handler::write_callback(BLECharacteristic& chr, uint8_t* data, uint16_t len, uint16_t offset)
{
  extern BLE_Handler BLE;
  BLE.ReceiveEvent((char*)data, len);
}

//Send a token via BT
void BLE_Handler::SendEvent(Token* Event)
{
    String payload = Event->getEventString();
    char sendData[20] = {0};
    payload.toCharArray(sendData, payload.length()+1);
    char1.notify(sendData, payload.length()+1);
    Serial.print("**Event sent: "); Serial.print(payload); Serial.println("**");
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

    if(Command == NULL) return;
    else {
        String temp = Command->getEventString();
        Serial.print("**Command received: "); Serial.print(temp); Serial.println("**");
    }   

    if(Command->FirstValue == String("led")) {
        if     (Command->SecondValue == String("on"))    feedback_handle.setColor(Command->ThirdValue);
        else if(Command->SecondValue == String("blink")) feedback_handle.blink(Command->ThirdValue);
        else if(Command->SecondValue == String("fade"))  feedback_handle.fade(Command->ThirdValue);
        else if(Command->SecondValue == String("off"))   feedback_handle.setColor(Command->SecondValue);
    }
    
    else if(Command->FirstValue == String("haptic")) {
        if     (Command->SecondValue == String("burst"))      feedback_handle.burst();
        else if(Command->SecondValue == String("short"))      feedback_handle.shortv();
        else if(Command->SecondValue == String("long"))       feedback_handle.longv();
        else if(Command->SecondValue == String("raise"))      feedback_handle.raise();
        else if(Command->SecondValue == String("fall"))       feedback_handle.fall();
        else if(Command->SecondValue == String("raise-fall")) feedback_handle.raiseFall();
        else feedback_handle.Vibrate(Command->SecondValue);
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
    else if(Command->FirstValue == String("shut"))
    {
        digitalWrite(PIN_LED_RED, LOW);
        delay(2000);
        digitalWrite(PIN_LED_RED, HIGH);
        if(BT_LED) digitalWrite(BT_LED, LOW);
        shutdown();
    }
    else if(Command->FirstValue == String("sound")) {
        if     (Command->SecondValue == String("up"))    feedback_handle.buzz(ON_S);
        else if(Command->SecondValue == String("down"))   feedback_handle.buzz(OFF_S);
        else if(Command->SecondValue == String("siren")) feedback_handle.buzz(SIREN);
        else Serial.println("**Buzzer parameter unknown**");
    }

    else Serial.println("**COMMAND NOT RECOGNIZED**");
}

void BLE_Handler::shutdown() {
    Serial.println("Tile shutting down");
    delay(20);
    systemOff(BUTTON_PIN, LOW);  // wake up interrupt
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

