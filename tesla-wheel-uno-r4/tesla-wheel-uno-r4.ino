#include <Servo.h>

Servo myWheel;

const int CENTER = 90;
const int ANGLE_OFFSET = 17;

const int STEP_DELAY = 20;   // ms between each degree step — increase to sweep slower

const int DELAY_MIN = 7000;
const int DELAY_MAX = 17000;

void sweepTo(int target) {
  int current = myWheel.read();
  if (current < target) {
    for (int pos = current; pos <= target; pos++) {
      myWheel.write(pos);
      delay(STEP_DELAY);
    }
  } else {
    for (int pos = current; pos >= target; pos--) {
      myWheel.write(pos);
      delay(STEP_DELAY);
    }
  }
}

void setup() {
  myWheel.attach(9);
  Serial.begin(115200);

  Serial.println("--- LEGO TESLA VOLUME KNOB STARTED ---");

  sweepTo(CENTER + ANGLE_OFFSET);
  delay(300);
  sweepTo(CENTER - ANGLE_OFFSET);
  delay(300);

  Serial.println("Startup done - now running continuously");
}

void loop() {

  delay(random(DELAY_MIN, DELAY_MAX + 1));
  sweepTo(CENTER + ANGLE_OFFSET);

  delay(random(DELAY_MIN, DELAY_MAX + 1));
  sweepTo(CENTER - ANGLE_OFFSET);

}