#include <Arduino.h>
#include <ESP32Servo.h>

Servo myServo;

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  myServo.attach(D6);
  Serial.println("Servo test started");
}

void loop() {
  // Sweep 0 to 180
  Serial.println("-> 180");
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, HIGH);
  myServo.write(180);
  delay(1000);

  // Sweep back to 0
  Serial.println("-> 0");
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);
  myServo.write(0);
  delay(1000);
}
