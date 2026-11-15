
#define MQ2_DO_PIN D6

void setup() {
  Serial.begin(115200);
  pinMode(MQ2_DO_PIN, INPUT);

  Serial.println("MQ-2 Digital Input Test");
}

void loop() {
  int gasValue = digitalRead(MQ2_DO_PIN);

  Serial.print("MQ-2 Digital Output: ");
  Serial.println(gasValue);

  delay(500);
}
