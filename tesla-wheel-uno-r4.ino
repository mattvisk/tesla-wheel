#include <ESP32Servo.h>

Servo myWheel;
int currentPos = 90;

void moveA() {
  currentPos += 30;
  myWheel.write(currentPos);
  Serial.println(">> Move A (+30)");
}

void moveB() {
  currentPos -= 30;
  myWheel.write(currentPos);
  Serial.println(">> Move B (-30)");
}

void setup() {
  myWheel.attach(9);
  Serial.begin(115200);

  myWheel.write(currentPos);
  delay(500);

  Serial.println("--- START ---");
  moveA();
}

void loop() {
  long waitTime = random(7000, 16001);
  Serial.print("Waiting ");
  Serial.print(waitTime / 1000);
  Serial.println("s...");
  delay(waitTime);

  moveB();

  waitTime = random(7000, 16001);
  Serial.print("Waiting ");
  Serial.print(waitTime / 1000);
  Serial.println("s...");
  delay(waitTime);

  moveA();
}
