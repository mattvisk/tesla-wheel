#include <ESP32Servo.h>

Servo myWheel;

void setup() {
  myWheel.attach(9);
  randomSeed(analogRead(0));
  Serial.begin(115200);

  Serial.println("--- BOOTING SYSTEM ---");

  // Startup jiggle
  myWheel.write(110); delay(200);
  myWheel.write(70);  delay(200);
  myWheel.write(110); delay(200);
  myWheel.write(70);  delay(200);
  myWheel.write(110); delay(200);
  myWheel.write(90);

  Serial.println("Handshake Complete. Waiting for first cycle...");
  delay(2000);
}

void loop() {
  long waitTime = random(8000, 18001);
  Serial.print("Next move in: ");
  Serial.print(waitTime / 1000);
  Serial.println("s...");
  delay(waitTime);

  Serial.println(">> ACTION");
  myWheel.write(0);
  delay(400);
  myWheel.write(45);
  delay(400);
  myWheel.write(0);
  Serial.println("<< STOPPED.");
  Serial.println("-------------------------");
}
