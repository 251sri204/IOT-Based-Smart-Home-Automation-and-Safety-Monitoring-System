
#define FSR_PIN A0

void setup() {
  Serial.begin(115200);
}

void loop() {
  int fsrValue = analogRead(FSR_PIN);

  Serial.print("FSR Pressure Reading: ");
  Serial.println(fsrValue);

  delay(500);
}
