#include <Servo.h>

Servo myWheel;

// ====================== SETTINGS ======================
const bool TEST_MODE = false;    // Set to true to halve delays for faster testing

const int CENTER = 90;           // Middle position for the knob
const int SWING_DEGREES = 7;     // How many degrees left/right it turns from center

const int MS_PER_DEGREE = 6;     // v5: slightly slower with easing for smoother, quieter movement

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
  int steps = abs(target - current);
  if (steps == 0) { servoDetach(); return; }

  int dir = (target > current) ? 1 : -1;

  for (int i = 0; i < steps; i++) {
    int pos = current + dir * (i + 1);
    myWheel.write(pos);

    // Sinusoidal ease-in/out: slow at ends, fast in the middle
    float t = (float)i / (steps - 1);  // 0.0 → 1.0
    float ease = 0.5 - 0.5 * cos(PI * t);  // 0.0 → 1.0 smoothly
    int ms = (int)(MS_PER_DEGREE * 3 * (1.0 - ease) + MS_PER_DEGREE * 0.5);
    delay(ms);
  }

  delay(50);
  servoDetach();
}


// ====================== SETUP ======================
void setup() {
  Serial.begin(115200);
  Serial.println("--- TESLA WHEEL UNO R4 v5 ---");
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
