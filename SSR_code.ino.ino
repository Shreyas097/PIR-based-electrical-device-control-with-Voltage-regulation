int relay = 7;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relay,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(relay,LOW); // Turns ON Relays 1
  Serial.println("Light On");
  delay(10000); // Wait 2 seconds
  digitalWrite(relay,HIGH); // Turns Relay Off
  Serial.println("Light Off");
  delay(10000);
}
