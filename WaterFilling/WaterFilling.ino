// Pin configuration
const int irSensorPin = 2;     // Replace with the actual pin connected to the IR sensor
const int pumpPin = 3;         // Replace with the actual pin connected to the pump
const int conveyorBeltPin = 4; // Replace with the actual pin connected to the conveyor belt

// Other parameters
const int irThreshold = 500;   // Adjust this value based on your IR sensor readings
const int fillTime = 5000;     // Adjust this value based on the time needed to fill the bottle

void setup() {
  pinMode(irSensorPin, INPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(conveyorBeltPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int irValue = analogRead(irSensorPin);

  if (irValue < irThreshold) {
    // Bottle detected, stop the conveyor belt and start filling
    stopConveyorBelt();
    startFilling();
  } else {
    // No bottle detected, resume the conveyor belt and stop filling
    startConveyorBelt();
    stopFilling();
  }
}

void startFilling() {
  Serial.println("Bottle detected. Filling...");

  digitalWrite(pumpPin, HIGH);  // Turn on the pump

  // Wait for the specified fill time
  delay(fillTime);

  stopFilling();
}

void stopFilling() {
  digitalWrite(pumpPin, LOW);   // Turn off the pump
  Serial.println("Filling stopped.");

  // Optional delay to avoid rapid on/off cycles
  delay(1000);
}

void startConveyorBelt() {
  digitalWrite(conveyorBeltPin, HIGH);  // Turn on the conveyor belt
}

void stopConveyorBelt() {
  digitalWrite(conveyorBeltPin, LOW);   // Turn off the conveyor belt
}
