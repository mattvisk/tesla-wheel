#include <Servo.h>

Servo myWheel;

// ====================== SETTINGS ======================
const bool TEST_MODE = false;    // Set to true to halve delays for faster testing

const int CENTER = 90;           // Middle position for the knob
const int SWING_DEGREES = 10;    // How many degrees left/right it turns from center

const int MS_PER_DEGREE = 4;     // v3: faster sweep (was 8) — snappier move, less servo strain/noise

const int SERVO_PIN = 9;

const int MIN = 9000;
const int MAX = 17000;

const int DELAY_MIN = TEST_MODE ? MIN / 2 : MIN;
const int DELAY_MAX = TEST_MODE ? MAX / 2 : MAX;

// How long the whole thing runs before stopping
const unsigned long RUN_TIME_MS = 2UL * 60 * 60 * 1000;  // 2 hours

// ====================== VARIABLES ======================
unsigned long startTime = 0;
bool running = true;


// ====================== HELPER FUNCTIONS ======================

void servoAttach() {
  if (!myWheel.attached()) {
    myWheel.attach(SERVO_PIN);
    delay(20);  // Brief settle time after attach
  }
}

void servoDetach() {
  if (myWheel.attached()) {
    myWheel.detach();
  }
}

void sweepTo(int target) {
  if (!running) return;

  servoAttach();

  int current = myWheel.read();

  if (current < target) {
    for (int pos = current; pos <= target; pos++) {
      myWheel.write(pos);
      delay(MS_PER_DEGREE);
    }
  } else {
    for (int pos = current; pos >= target; pos--) {
      myWheel.write(pos);
      delay(MS_PER_DEGREE);
    }
  }

  // v2: detach after reaching position — servo stops drawing hold current,
  // eliminates buzzing/chatter caused by battery voltage sag under load
  delay(50);       // Brief pause to let servo settle at position
  servoDetach();
}


// ====================== SETUP ======================
void setup() {
  Serial.begin(115200);
  Serial.println("--- TESLA WHEEL UNO R4 v3 ---");
  Serial.println("Running for 2 hours then stopping.");

  startTime = millis();

  // Startup wiggle from known center
  servoAttach();
  myWheel.write(CENTER);
  delay(500);

  sweepTo(CENTER + SWING_DEGREES);
  delay(300);
  sweepTo(CENTER - SWING_DEGREES);
  delay(300);
  sweepTo(CENTER);

  Serial.println("Ready! Servo detaches between moves to reduce noise.");
}


// ====================== MAIN LOOP ======================
void loop() {

  // === Time check: Should we stop? ===
  if (running && (millis() - startTime >= RUN_TIME_MS)) {
    Serial.println("2 hours up! Signing off...");
    // 3 goodbye movements
    for (int i = 0; i < 3; i++) {
      sweepTo(CENTER + SWING_DEGREES);
      delay(500);
      sweepTo(CENTER - SWING_DEGREES);
      delay(500);
    }
    sweepTo(CENTER);
    servoDetach();
    running = false;
  }

  if (!running) {
    delay(1000);
    return;
  }

  // === Normal movement ===
  // Servo is detached during pauses — quiet, no hold current drain
  delay(random(DELAY_MIN, DELAY_MAX + 1));
  sweepTo(CENTER + SWING_DEGREES);

  delay(random(DELAY_MIN, DELAY_MAX + 1));
  sweepTo(CENTER - SWING_DEGREES);
}
