#include <Servo.h>

Servo myWheel;

const int CENTER = 90;
const int ANGLE_OFFSET = 25;

void setup() {
  myWheel.attach(9);
  Serial.begin(115200);

  Serial.println("--- LEGO TESLA VOLUME KNOB STARTED ---");

  // === Simple startup movement to ensure it's working ===
  myWheel.write(CENTER + ANGLE_OFFSET);    // +X°
  delay(300);

  myWheel.write(CENTER - ANGLE_OFFSET);   // -X°
  delay(300);

  Serial.println("Startup done - now running continuously");
}

void loop() {

  delay(random(7000, 17001));
  myWheel.write(CENTER + ANGLE_OFFSET);   // +X°

  delay(random(7000, 17001));
  myWheel.write(CENTER - ANGLE_OFFSET);    // -X°

}