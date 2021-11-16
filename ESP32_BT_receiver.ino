
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

String MACadd = "00:21:06:08:4A:1C";
//uint8_t address[6]  = {0x00, 0x21, 0x06, 0x08, 0x4A, 0x1C};
uint8_t address[6]  = {0x00, 0x21, 0x06, 0x08, 0x4A, 0x1C};
String name = "ORCH";
char *pin = "1234"; //<- standard pin would be provided by default
bool connected;
unsigned long cm, pm;
int interval = 5000;

void setup() {

  pinMode(2,OUTPUT); digitalWrite(2,0);
  Serial.begin(115200);
  //SerialBT.setPin(pin);
  SerialBT.begin("ORCH_MB", true); 
  //SerialBT.setPin(pin);
  Serial.println("The device started in master mode, make sure remote BT device is on!");
  
  // connect(address) is fast (upto 10 secs max), connect(name) is slow (upto 30 secs max) as it needs
  // to resolve name to address first, but it allows to connect to different devices with the same name.
  // Set CoreDebugLevel to Info to view devices bluetooth address and device names
  //connected = SerialBT.connect(name);
  connected = SerialBT.connect(address);
  
  if(connected) 
  {
    Serial.println("Connected Succesfully!");
  } 
  else 
  {
    while(!SerialBT.connected(10000)) 
    {
      connected = SerialBT.connect(name);
      //Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app."); 
      Serial.println(".."); 
    }
  }

  // this would reconnect to the name(will use address, if resolved) or address used with connect(name/address).
  SerialBT.connect();
  if(SerialBT.connected()){digitalWrite(2,1);Serial.println("Connected."); }
}

void loop() {

  if (SerialBT.available()) 
  {Serial.write(SerialBT.read());}
  
 cm=millis();
  if ((cm-pm)>=interval)
  {
    //Serial.println(cm-pm);
  if(SerialBT.connected())
  {/*Serial.println("connected");*/ digitalWrite(2,1);}
  else
  {
    /*Serial.println("not connected");*/ digitalWrite(2,0);
    SerialBT.connect();
  }
  pm=millis();
  }
}
