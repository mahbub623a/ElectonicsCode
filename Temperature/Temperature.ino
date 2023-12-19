#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2  // Connect the signal pin of the DHT sensor to digital pin 2
#define DHTTYPE DHT22  // Change this to DHT11 if you are using that sensor
DHT dht(DHTPIN, DHTTYPE);

// LCD Setup
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Change the address (0x27) according to your LCD's address

// Fan control
const int fanPin = 3;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Initialize DHT sensor
  dht.begin();

  // Initialize LCD
  lcd.begin(16, 2);

  // Initialize fan pin
  pinMode(fanPin, OUTPUT);
}

void loop() {
  // Read temperature and humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Display temperature and humidity on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");

  // Control fan based on temperature
  if (temperature > 25.0) {
    digitalWrite(fanPin, HIGH);  // Turn on the fan
  } else {
    digitalWrite(fanPin, LOW);  // Turn off the fan
  }

  // Print temperature and humidity to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(2000);  // Delay for 2 seconds
}
