#include <Arduino.h>

#define LED_PIN 2  // Define el pin al que está conectado el LED

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);  // Configura el pin del LED como salida
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED is on");
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED is off");
  delay(1000);
}
