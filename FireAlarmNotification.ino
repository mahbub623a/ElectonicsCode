#define BLYNK_TEMPLATE_ID "TMPL6MPr4mSbt"
#define BLYNK_TEMPLATE_NAME "UG Fire Alert System"
#define BLYNK_AUTH_TOKEN "nQ4pqRgl81IlcEi9FdiKjhYbxDa0Phxi"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "nQ4pqRgl81IlcEi9FdiKjhYbxDa0Phxi";
char ssid[] = "UIU_Boyz";  // type your wifi name
char pass[] = "mhs@54321";  // type your wifi password

int buzzerPin = D2;  // Change D2 to the pin where you connect the buzzer

BlynkTimer timer;
int flag = 0;

void sendSensor() {
  int isButtonPressed = digitalRead(D1);
  if (isButtonPressed == 0 && flag == 0) {
    Serial.println("Fire in the Factory");
    Blynk.logEvent("fire_alert", "Fire Detected");

    // Turn on the buzzer
    digitalWrite(buzzerPin, HIGH);
    
    flag = 1;
  } else if (isButtonPressed == 1) {
    flag = 0;
    // Turn off the buzzer
    digitalWrite(buzzerPin, LOW);
  }
}

void setup() {
  pinMode(D1, INPUT);
  pinMode(buzzerPin, OUTPUT);  // Set the buzzer pin as an output
  
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}