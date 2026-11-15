
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

// -------- Wi-Fi details --------
const char* ssid = "OnePlus 13s (V)";
const char* password = "Wasd_gaming!";

// -------- ThingSpeak details --------
unsigned long channelNumber = 3578367;
const char* writeAPIKey = "MOU6SFGWWVCW1IZA";

// -------- Pin configuration --------
#define FSR_PIN A0
#define MQ2_DO_PIN D6
#define RELAY_PIN D5

const int FSR_THRESHOLD = 200;

WiFiClient client;

void setup() {
  Serial.begin(115200);

  pinMode(MQ2_DO_PIN, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);

  // Relay OFF (active LOW)
  digitalWrite(RELAY_PIN, HIGH);

  Serial.println();
  Serial.println("SMART MONITORING IOT SYSTEM");

  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
}

void loop() {

  // Read sensors
  int pressureValue = analogRead(FSR_PIN);
  int gasValue = digitalRead(MQ2_DO_PIN);

  // Control relay using FSR
  if (pressureValue >= FSR_THRESHOLD) {
    digitalWrite(RELAY_PIN, LOW);
  } else {
    digitalWrite(RELAY_PIN, HIGH);
  }

  // Reconnect Wi-Fi if disconnected
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
  }

  Serial.println("--------------------------");
  Serial.print("Pressure: ");
  Serial.println(pressureValue);

  Serial.print("MQ-2 Gas Digital Output: ");
  Serial.println(gasValue);

  // Send readings to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {

    ThingSpeak.setField(1, pressureValue);
    ThingSpeak.setField(2, gasValue);

    int response = ThingSpeak.writeFields(
      channelNumber,
      writeAPIKey
    );

    if (response == 200) {
      Serial.println("ThingSpeak update successful!");
    } else {
      Serial.print("ThingSpeak error code: ");
      Serial.println(response);
    }

  } else {
    Serial.println("Wi-Fi disconnected!");
  }

  delay(20000);
}
