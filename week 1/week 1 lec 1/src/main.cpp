#include <Arduino.h>

#define LED 2   // Built-in LED on ESP32

void setup() {
  pinMode(LED, OUTPUT);  // LED pin as output
}

void loop() {
  digitalWrite(LED, HIGH);  // LED ON
  delay(500);               // wait 0.5 second
  digitalWrite(LED, LOW);   // LED OFF
  delay(500);               // wait 0.5 second
}
