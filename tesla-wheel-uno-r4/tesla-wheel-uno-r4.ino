#include <Servo.h>

Servo myWheel;

const int CENTER = 90;
const int ANGLE_OFFSET = 22;

void setup() {
  myWheel.attach(9);
  Serial.begin(115200);

  Serial.println("--- LEGO TESLA VOLUME KNOB STARTED ---");

  // === Simple startup movement to ensure it's working ===
  myWheel.write(CENTER - ANGLE_OFFSET);    // 0°
  delay(500);

  myWheel.write(CENTER + ANGLE_OFFSET);   // +22°
  delay(500);

  Serial.println("Startup done - now running continuously");
}

void loop() {

  delay(random(7000, 17001));
  myWheel.write(CENTER + ANGLE_OFFSET);   // +22°
  Serial.println(">> +22°");

  delay(random(7000, 17001));
  myWheel.write(CENTER - ANGLE_OFFSET);    // -22°
  Serial.println(">> -22°");

}