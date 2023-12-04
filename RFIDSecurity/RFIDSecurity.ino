#include <Servo.h>
#include <MFRC522.h>
#include <SPI.h>

// Pin Connection
#define SS_PIN 10  // Slave Select pin for MFRC522 RFID module (SDA)
#define RST_PIN 9  // Reset pin for MFRC522 RFID module
// SCK -> 13
// MOSI -> 11
// MISO -> 12

Servo lockServo;

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lockServo.attach(6);  // Connect the servo signal pin to digital pin 6
  
  lockServo.write(0);  // Initially door will be locked
}

void loop() {
  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Print UID
    Serial.print("Card UID: ");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();

    // Check if the card is authorized
    if (isAuthorized()) {
      unlockDoor();
    } else {
      Serial.println("Access denied!");
    }

    delay(1000);  // Delay to prevent multiple readings
    mfrc522.PICC_HaltA();
  }
}

bool isAuthorized() {  
// Replace the following with your authorized card UID
byte authorizedCardUID[] = {0x33, 0x3F, 0x15, 0xAD};

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] != authorizedCardUID[i]) {
      return false;
    }
  }

  return true;
}

void unlockDoor() {
  Serial.println("Access granted! Door Unlocked.");
  lockServo.write(90);  // Rotate the servo motor to unlock position
  delay(4000);  // Keep the door unlocked for 3 seconds
  lockServo.write(0);  // Rotate the servo motor back to lock position
  Serial.println("Door Locked.");
}
