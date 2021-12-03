
#include "BluetoothSerial.h"
#include <SimpleDHT.h>

BluetoothSerial SerialBT;
int pinDHT11 = 15;
SimpleDHT11 dht11(pinDHT11);

String MACadd = "00:21:06:08:4A:1C";
//uint8_t address[6]  = {0x00, 0x21, 0x06, 0x08, 0x4A, 0x1C};
uint8_t address[6]  = {0x00, 0x21, 0x06, 0x08, 0x4A, 0x1C};
String name = "ORCH";
char *pin = "1234"; //<- standard pin would be provided by default
bool connected;
unsigned long cm, pm;
int interval = 5000;
byte temperature = 0;
byte humidity = 0;

void setup() {

  pinMode(2,OUTPUT); digitalWrite(2,0);
  Serial.begin(115200);
  SerialBT.begin("ORCH_MB", true); 
  Serial.println("The device started in master mode, make sure remote BT device is on!");
  
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
      Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app."); 
    }
  }

  // this would reconnect to the name(will use address, if resolved) or address used with connect(name/address).
  SerialBT.connect();
  if(SerialBT.connected()){digitalWrite(2,1);}
}

void loop() {

  if (SerialBT.available()) 
  {
    //Serial.print("Body temperature: ");
    String C = String(SerialBT.read());
  Serial.print("B1: ");Serial.write(SerialBT.read());
  Serial.print("     B2: ");Serial.println(C);
  //Serial.println(" *F");//delay(500);
  }
  
  
//*******************************************************

  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) 
  {
    Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }
  //Serial.print((int)temperature); Serial.print(" *C, "); 
  //Serial.print((int)humidity); Serial.println(" H");
  
  delay(1500);
  
//*******************************************************
  
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
  
}//loop
