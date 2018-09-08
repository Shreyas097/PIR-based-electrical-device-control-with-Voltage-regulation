/*

 AC Light Dimmer v.2 - Inmojo 
 AC Voltage dimmer with Zero cross detection
 
 Author: Charith Fernanado http://www.inmojo.com charith@inmojo.com 
 License: Released under the Creative Commons Attribution Share-Alike 3.0 License. 
 http://creativecommons.org/licenses/by-sa/3.0
 Target:  Arduino
 
 Attach the Zero cross pin of the module to Arduino External Interrupt pin
 Select the correct Interrupt # from the below table
 
 Pin    |  Interrrupt # | Arduino Platform
 ---------------------------------------
 2      |  0            |  All
 3      |  1            |  All
 18     |  5            |  Arduino Mega Only
 19     |  4            |  Arduino Mega Only
 20     |  3            |  Arduino Mega Only
 21     |  2            |  Arduino Mega Only
 
 Please select your utility power frequency from frq variable.
 
 */
#define  fullOn    10
#define  fullOff   127
#define  FQ_50      1 // in case of 50Hz
#define  FQ_60      0 // in case of 50Hz
#define  VER       "2.0"

int inbyte;
int AC_LOAD = 11;    // Output to Opto Triac pin
int dimming = fullOff;  // Dimming level (0-128)  0 = ON, 128 = OFF
int pir = 7;        // Input from PIR Sensor
int tempPin = A5;

boolean frq = FQ_50;     // change the frequency here. 
int countUp = 0;
boolean simulate = false; 
//boolean simulate = true;
int k = 1;
boolean val = false;
int temp_val = 0;
void setup()
{
  pinMode(AC_LOAD, OUTPUT);        // Set the AC Load as output
  attachInterrupt(1, zero_crosss_int, RISING);  // Choose the zero cross interrupt # from the table above
  Serial.begin(115200);
}

void zero_crosss_int()  // function to be fired at the zero crossing to dim the light
{
  // Firing angle calculation
  // 50Hz-> 10ms (1/2 Cycle) → (10000us - 10us) / 128 = 78 (Approx)
  // 60Hz-> 8.33ms (1/2 Cycle) → (8333us - 8.33us) / 128 = 65 (Approx)
  int dimtime = 0;
  float propTime = 0;
  if(frq){
    dimtime = (78 *dimming);
    propTime = 10.0; 
  }
  else{
    dimtime = (65*dimming);
    propTime = 8.33; 
  }
  //Serial.println(dimtime);
  delayMicroseconds(dimtime);    // Off cycle
  if(dimtime > 9600)
  goto skip;
  digitalWrite(AC_LOAD, HIGH);   // triac firing
  delayMicroseconds(propTime);         // triac On propogation delay
  skip:
  digitalWrite(AC_LOAD, LOW);    // triac Off

}

void loop()
{
  repeat:
  temp_val = analogRead(tempPin);
  float mv = ( temp_val/1024.0)*5000; 
  float cel = mv/10;
 
  if (cel > 0 && cel <= 20)           //Change LDR values here
    countUp = 0;
  else if (cel > 20 && cel <= 25)
    countUp = 1;
  else if (cel > 25 && cel <= 30)
    countUp = 2;
  else if (cel > 30 && cel <= 35)
    countUp = 3;
  else
    countUp = 4;

  val = digitalRead(pir);
  if (val == true)
  {
    simulate = true;
    Serial.println("Motion detected");
  }

  if(simulate == true){
    simulate = false;
    int x = 9600;
    Serial.println(cel);
    Serial.println(countUp);              
    if(countUp == 0)
      dimming = 128;
    else if(countUp == 1)
      dimming = 120; 
    else if(countUp == 2)
      dimming = 95;
    else if(countUp == 3)
      dimming = 75;  
    else 
      dimming = 45;
    int b=x;     //Change delay value here
    int flag=0;
    for(x=b;x>0;x--)
    {
      Serial.println(x);
      Serial.println(x);
      if(digitalRead(pir)==HIGH)
        flag=1;
    }
    if(flag==1)
    {
      simulate = true;
      Serial.println("Motion detected during high state!"); 
      goto repeat;
    }
  }
  else
    dimming = 128;


}

//void delay1(int x)
//{
//  int b=x;
//  repeat:
//  int flag=0;
//  for(x=b;x>0;x--)
//  {
//    Serial.println(x);
//    if(digitalRead(PIR_sensor)==HIGH)
//      flag=1;
//  }
//  if(flag==1)
//  {
//    Serial.println("Motion detected during high state!"); 
//    goto repeat;
//  }
//}


