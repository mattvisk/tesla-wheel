#include <Servo.h>

Servo myWheel;

const int CENTER = 90;
const int ANGLE_OFFSET = 17;

const int SPEED = 1; 

const int DELAY_MIN = 7000 / SPEED;
const int DELAY_MAX = 17000 / SPEED;

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

  delay(random(DELAY_MIN, DELAY_MAX + 1));
  myWheel.write(CENTER + ANGLE_OFFSET);   // +X°

  delay(random(DELAY_MIN, DELAY_MAX + 1));
  myWheel.write(CENTER - ANGLE_OFFSET);    // -X°

}