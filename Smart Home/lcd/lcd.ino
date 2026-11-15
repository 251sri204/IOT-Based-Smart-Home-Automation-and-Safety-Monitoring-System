
#include <Servo.h>

// Pin assignments
#define FSR_PIN A0
#define RELAY_PIN D5
#define MQ2_PIN D6
#define SERVO_PIN D7

// Relay is active LOW
#define RELAY_ON LOW
#define RELAY_OFF HIGH

// FSR threshold verified during testing
#define FSR_THRESHOLD 200

Servo myServo;

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, RELAY_OFF);

  pinMode(MQ2_PIN, INPUT);

  // Software control only until servo has a safe external supply
  myServo.attach(SERVO_PIN);
  myServo.writeMicroseconds(1500);

  Serial.println();
  Serial.println("IoT Safety Monitoring System");
  Serial.println("----------------------------");
}

void loop() {
  int fsrValue = analogRead(FSR_PIN);
  int mq2Value = digitalRead(MQ2_PIN);

  bool pressureDetected = (fsrValue > FSR_THRESHOLD);

  // Verified function: FSR controls relay
  if (pressureDetected) {
    digitalWrite(RELAY_PIN, RELAY_ON);
    myServo.writeMicroseconds(1700);
  } else {
    digitalWrite(RELAY_PIN, RELAY_OFF);
    myServo.writeMicroseconds(1500);
  }

  // Display readings for monitoring
  Serial.print("FSR: ");
  Serial.print(fsrValue);

  Serial.print(" | MQ-2 Digital: ");
  Serial.print(mq2Value);

  Serial.print(" | Pressure: ");
  Serial.print(pressureDetected ? "DETECTED" : "NOT DETECTED");

  Serial.print(" | Relay: ");
  Serial.println(pressureDetected ? "ON" : "OFF");

  delay(500);
}
