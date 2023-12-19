#define BLYNK_TEMPLATE_ID "TMPL6MPr4mSbt"
#define BLYNK_TEMPLATE_NAME "UG Fire Alert System"
#define BLYNK_AUTH_TOKEN "nQ4pqRgl81IlcEi9FdiKjhYbxDa0Phxi"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "nQ4pqRgl81IlcEi9FdiKjhYbxDa0Phxi";
char ssid[] = "UIU-STUDENT";  // Wifi name
char pass[] = "12345678";  // Wifi password

int sensorPin = D1; // Connect the sensor
int buzzerPin = D2;  //  Connect the buzzer
int redLightPin = D3;  // Connect the red light
int greenLightPin = D4;  // Connect the green light

BlynkTimer timer;

void sendSensorInfo() {
  int sensorInfo = digitalRead(sensorPin);

  if (sensorInfo == 1) {

    Serial.println("Fire in the Factory");
    Blynk.logEvent("fire_alert", "Fire detected in your factory.");

    // Turn on the red light
    digitalWrite(redLightPin, HIGH);
    // Turn off the green light
    digitalWrite(greenLightPin, LOW);

    // Turn on the buzzer
    digitalWrite(buzzerPin, HIGH);
    
  } else {

    // Turn off the red light
    digitalWrite(redLightPin, LOW);
    // Turn on the green light
    digitalWrite(greenLightPin, HIGH);

    // Turn off the buzzer
    digitalWrite(buzzerPin, LOW);

  }
}

void setup() {

  pinMode(sensorPin, INPUT); // Set the sensor pin as input
  pinMode(buzzerPin, OUTPUT);  // Set the buzzer pin as an output
  pinMode(redLightPin, OUTPUT);  // Set the red light pin as an output
  pinMode(greenLightPin, OUTPUT);  // Set the green light pin as an output
  
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensorInfo);

}

void loop() {

  Blynk.run();
  timer.run();

}