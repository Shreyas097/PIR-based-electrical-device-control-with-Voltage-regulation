int sensorPin = A0; // select the input pin for LDR
int sensorValue = 0; // variable to store the value coming from the sensor

void setup() {
  pinMode(sensorPin,INPUT);
  Serial.begin(9600); //sets serial port for communication
}

void loop() {
sensorValue = analogRead(sensorPin); // read the value from the sensor
float volts = (sensorValue/1023.0)*5.0;
int lux=(2500/volts-500)/1;
Serial.print("Sensor value:");
Serial.println(sensorValue); //prints the values coming from the sensor on the screen
Serial.print("Volts:");
Serial.println(volts);
Serial.print("Lux value:");
Serial.println(lux);
delay(3000);
}

//int sensorPin = A0; // select the input pin for LDR
//int sensorValue = 0; // variable to store the value coming from the sensor
//void setup() {
//Serial.begin(9600); //sets serial port for communication
//}
//void loop() {
//sensorValue = analogRead(sensorPin); // read the value from the sensor
//Serial.println(sensorValue); //prints the values coming from the sensor on the screen
//delay(1000);
//}


