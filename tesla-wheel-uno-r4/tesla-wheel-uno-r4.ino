#include <Servo.h>        // ← Standard Servo library

Servo myWheel;
bool nextDirectionForward = true;

void setup() {
  myWheel.attach(9);      // Pin 9 works great on R4 WiFi
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

  if (nextDirectionForward) {
    Serial.println(">> Spinning FORWARD");
    myWheel.write(180);
  } else {
    Serial.println(">> Spinning BACKWARD");
    myWheel.write(0);
  }

  delay(random(500, 1201));
  myWheel.write(90);
  Serial.println("<< STOPPED.");
  Serial.println("-------------------------");

  nextDirectionForward = !nextDirectionForward;
}