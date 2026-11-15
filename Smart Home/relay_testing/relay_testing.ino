
#define RELAY_PIN D5

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);

  // Relay OFF (active LOW)
  digitalWrite(RELAY_PIN, HIGH);
}

void loop() {
  // Relay ON
  digitalWrite(RELAY_PIN, LOW);
  Serial.println("Relay ON");

  delay(2000);

  // Relay OFF
  digitalWrite(RELAY_PIN, HIGH);
  Serial.println("Relay OFF");

  delay(2000);
}
