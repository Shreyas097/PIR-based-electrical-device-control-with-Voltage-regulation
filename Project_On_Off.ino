int LDR_sensor = A5;   // select the input pin for ldr
int tempPin = A0; // input pin for lm35
int Lamp_led = 13;                // the pin that the Lamp_LED is atteched to
int Fan_led = 12;                 // the pin that the Fan_LED is atteched to
int PIR_sensor = 2;              // the pin that the sensor is atteched to
//int relay_light = 7;              // relay pin for lamp is attached
//int relay_fan = 8;                // relay pin for fan is attached
int val = 0; 
int temp_val;     
int ldr_val = 0; 
int fan_mode = 0;
int light_mode = 0;
      
void setup() {
  pinMode(PIR_sensor, INPUT);    // initialize PIR sensor as an input
  pinMode(LDR_sensor, INPUT);    // initialize LDR sensor as an input
  pinMode(tempPin, INPUT);    // initializeTemp sensor as an input
  pinMode(Lamp_led, OUTPUT);      // initalize Lamp LED as an output
  pinMode(Fan_led, OUTPUT);      // initalize Fan LED as an output
  //pinMode(relay_light,OUTPUT);    // initialize Lamp output
  //pinMode(relay_fan,OUTPUT);    // initialize Fan output
  Serial.begin(9600);       
}

void loop(){ 
  val = digitalRead(PIR_sensor);

  // Program for Fan
  temp_val = analogRead(tempPin);
  float cel = ( temp_val/1024.0)*500.0; 
  int cel_1 = 31;
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
  if(val == HIGH)       
  {   
      Serial.println("Motion detected(Fan)!"); 
//      if(cel <= 10) 
//        Serial.println("Ambient temp is very low & fan is not needed");       
//      else if(cel > 10 && cel <=20)
//        Serial.println("Ambient temp is low & low fan speed is needed");
//      else if(cel > 20 && cel <=30)
//        Serial.println("Ambient temp is moderate & moderate fan speed is needed"); 
//      else if(cel > 30 && cel <=40)
//        Serial.println("Ambient temp is high & high fan speed is needed");
//      else if(cel >40)
//        Serial.println("Ambient temp is highest & max fan speed is needed"); 
      if(cel_1 > 30)
      {
        fan_mode = 1;
      }
      else
      {
        fan_mode = 0;
        digitalWrite(Fan_led,LOW);
        //digitalWrite(relay_fan, HIGH);   // turn Fan ON
        Serial.println("Motion detected but Fan is OFF");
        delay(500);
      }
  }
  else 
  {
      fan_mode = 0;
      Serial.println("No Motion detected(Fan)!");
      digitalWrite(Fan_led, LOW); // turn LED OFF
      //digitalWrite(relay_fan,LOW); // turn Fan OFF
      delay(500);             // delay 200 milliseconds  
  }
  
  // Program for Light
  ldr_val = analogRead(LDR_sensor);
  float volts = (ldr_val/1024.0)*5.0;
  int lux=(2500/volts-500)/1;
  Serial.print("Lux value:");
  Serial.println(lux);
  if(val == HIGH)       
  {   
      Serial.println("Motion detected(Light)!"); 
//      if(lux > 0 && lux <= 30) 
//        Serial.println("Ambient light is very low & max brightness is needed");       
//      else if(lux > 30 && lux <=50)
//        Serial.println("Ambient light is low & low brightness is needed");
//      else if(lux > 50 && lux <=80)
//        Serial.println("Ambient light is moderate & moderate brightness is needed"); 
//      else if(lux > 80 && lux <=100)
//        Serial.println("Ambient light is high & min brightness is needed");
//      else
//        Serial.println("Ambient light is very high & no brightness is needed"); 
        
      //The below part is for On/OFF only
      if(lux <=50)
      {
        light_mode = 1;
      }
      else
      {
        light_mode = 0;
        digitalWrite(Lamp_led,LOW);
        //digitalWrite(relay_light,LOW); // turn Lamp OFF
        Serial.println("Motion detected but Lamp is OFF");
        delay(500);
      }
  } 
  else 
  {
      light_mode = 0;
      Serial.println("No Motion detected(Light)!");
      digitalWrite(Lamp_led, LOW); // turn LED OFF
      //digitalWrite(relay_light,LOW); // turn Lamp OFF
      delay(500);             // delay 200 milliseconds  
  }

  if(fan_mode == 1 && light_mode == 0)
  {
     Serial.println("Fan is on & Light is off");
     digitalWrite(Fan_led,HIGH);
     //digitalWrite(relay_fan,HIGH); // turn Fan ON
     delay1(4800);
  }
  else if(fan_mode == 0 && light_mode == 1)
  {
    Serial.println("Fan is off & Light is on");
    digitalWrite(Lamp_led,HIGH);
    //digitalWrite(relay_light,HIGH); // turn Lamp ON
    delay1(4800);
  }
  else if(fan_mode == 1 && light_mode == 1)
  {
    Serial.println("Fan is on & Light is on");
    digitalWrite(Fan_led,HIGH);
    //digitalWrite(relay_fan,HIGH); // turn Fan ON
    digitalWrite(Lamp_led,HIGH);
    //digitalWrite(relay_light,HIGH); // turn Lamp ON
    delay1(4800);
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
    if(digitalRead(PIR_sensor)==HIGH)
      flag=1;
  }
  if(flag==1)
  {
    Serial.println("Motion detected during high state!"); 
    goto repeat;
  }
}

