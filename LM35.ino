int val;
int tempPin = A5;

void setup()
{
  Serial.begin(9600);
  pinMode(tempPin,INPUT);
}
void loop()
{
  val = analogRead(tempPin);
  float mv = ( val/1024.0)*5000; 
  float cel = mv/10;

  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
  delay(1000);

  //uncomment this to get temperature in farenhite 
  /*Serial.print("TEMPRATURE = ");
  Serial.print(farh);
  Serial.print("*F");
  Serial.println();*/
  if (cel > 31)
  {
     Serial.println("Light On");
  }
}
