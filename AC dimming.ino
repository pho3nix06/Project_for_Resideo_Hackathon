int x,y;
const byte button_pin = 13;

const byte trig = 2;
int f=0;
boolean message = false;
unsigned long cm,pm;

void IRAM_ATTR got_function()
{
//  if (f <= 300)
//  {
  Serial.print("lt");
  Serial.println(micros()-pm);
  cm = micros();
  delayMicroseconds(x);
  digitalWrite(trig,1);
  delayMicroseconds(10);
  digitalWrite(trig,0);
  Serial.print("DT+TRIG");
  Serial.println(micros()-cm);
  pm = micros();
  Serial.println(x);
  //f++;
  //}
}



  
void setup() 
{

    Serial.begin(115200);
    
    pinMode(trig,OUTPUT);
    digitalWrite(trig,0);
    pinMode(button_pin,INPUT_PULLUP);
    pinMode(A18,INPUT);
    
    attachInterrupt(button_pin,got_function,FALLING);  
}

void loop() 
{
  y = analogRead(A18);
  x= map(y,0,4095, 200,19200);

}
