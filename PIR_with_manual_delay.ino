int LDR_sensor = A0;   // select the input pin for ldr
int Temp_sensor = A1; // input pin for lm35
int Lamp_led = 4;                // the pin that the Lamp_LED is atteched to
int Fan_led = 5;                 // the pin that the Fan_LED is atteched to
int PIR_sensor = 2;              // the pin that the sensor is atteched to
int relay = 7;              // relay pin for lamp is attached
int val = 0; 
int temp_val = 0;     
int ldr_val = 0; 
      
void setup() {
  pinMode(PIR_sensor, INPUT);    // initialize PIR sensor as an input
  pinMode(LDR_sensor, INPUT);    // initialize LDR sensor as an input
  pinMode(Lamp_led, OUTPUT);      // initalize Lamp LED as an output
  pinMode(Fan_led, OUTPUT);      // initalize Fan LED as an output
  pinMode(relay,OUTPUT);    // initialize Lamp output
  Serial.begin(9600);       
}

void loop(){ 
  val = digitalRead(PIR_sensor);
  
  // Program for Light
  ldr_val = analogRead(LDR_sensor);
  float volts = (ldr_val/1023.0)*5.0;
  int lux=(2500/volts-500)/10;
  Serial.print("Lux value w.r.t darkness");
  Serial.println(lux);
  int lux1=1024-lux;
  Serial.print("Lux value w.r.t brightness");
  Serial.println(lux1); 
  if(val == HIGH)       
  {   
      Serial.println("Motion detected(Light)!"); 
      if(lux > 0 && lux <= 200) 
        Serial.println("Ambient light is very low & max brightness is needed");       
      else if(lux > 200 && lux <=400)
        Serial.println("Ambient light is low & low brightness is needed");
      else if(lux > 400 && lux <=600)
        Serial.println("Ambient light is moderate & moderate brightness is needed"); 
      else if(lux > 600 && lux <=800)
        Serial.println("Ambient light is high & min brightness is needed");
      else
        Serial.println("Ambient light is very high & no brightness is needed"); 
        
      //The below part is for On/OFF only
      if(lux <=200)
      {
        digitalWrite(Lamp_led, HIGH);   // turn LED ON
        digitalWrite(relay, HIGH);   // turn Lamp ON
        Serial.println("Lamp & Lamp_LED on");
        delay1(9600);                // delay 1 minute
      }
  } 
  else 
  {
      Serial.println("No Motion detected(Light)!");
      digitalWrite(Lamp_led, LOW); // turn LED OFF
      digitalWrite(relay,LOW); // turn Lamp OFF
      delay(200);             // delay 200 milliseconds  
  }
  
  // Program for Fan
  temp_val = analogRead(Temp_sensor);
  float mv = (val/1024.0)*5000; 
  float cel = mv/10;

  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
  if(val == HIGH)       
  {   
      Serial.println("Motion detected(Fan)!"); 
      if(cel <= 10) 
        Serial.println("Ambient temp is very low & fan is not needed");       
      else if(cel > 10 && lux <=20)
        Serial.println("Ambient temp is low & low fan speed is needed");
      else if(lux > 20 && lux <=30)
        Serial.println("Ambient temp is moderate & moderate fan speed is needed"); 
      else if(lux > 30 && lux <=40)
        Serial.println("Ambient temp is high & high fan speed is needed");
      else if(lux >40)
        Serial.println("Ambient temp is highest & max fan speed is needed"); 
      if(temp > 30)
      {
        digitalWrite(fan_led, HIGH);   // turn LED ON
        //digitalWrite(relay, HIGH);   // turn Fan ON
        Serial.println("Fan & Fan_LED on);
        delay2(9600);                // delay 1 minute
      }
  }
  else 
  {
      Serial.println("No Motion detected(Fan)!");
      digitalWrite(Fan_led, LOW); // turn LED OFF
      //digitalWrite(relay,LOW); // turn Fan OFF
      delay(200);             // delay 200 milliseconds  
  }
}

void delay1(int x)
{
  int b=x;
  repeat:
  int flag=0;
  for(x=b;x>0;x--)
  {
    Serial.println(x);
    if(digitalRead(sensor)==HIGH)
      flag=1;
  }
  if(flag==1)
  {
    Serial.println("Motion detected during high state!"); 
    goto repeat;
  }
}

void delay2(int x)
{
  int b=x;
  repeat:
  int flag=0;
  for(x=b;x>0;x--)
  {
    Serial.println(x);
    if(digitalRead(sensor)==HIGH)
      flag=1;
  }
  if(flag==1)
  {
    Serial.println("Motion detected during high state!"); 
    goto repeat;
  }
}

