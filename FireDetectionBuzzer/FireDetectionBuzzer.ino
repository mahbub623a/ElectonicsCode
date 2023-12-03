#define Sensor 2
#define Buzzer 3
#define LED 4

void setup() {
  Serial.begin(9600);
  pinMode(Sensor, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
}

void loop() {
  bool value = digitalRead(Sensor);
  Serial.println(value);

  if (value == 1) {
    digitalWrite(LED, HIGH);
    digitalWrite(Buzzer, HIGH);
    // delay(1000); // Adjust the delay time according to your preference (in milliseconds)
    // digitalWrite(Buzzer, LOW); 
  } else {
    digitalWrite(LED, LOW);
    digitalWrite(Buzzer, LOW);
  }
}
