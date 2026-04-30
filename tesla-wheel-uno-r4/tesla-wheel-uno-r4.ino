#include <Servo.h>

Servo myWheel;

// ====================== SETTINGS ======================
const bool TEST_MODE = false;

const int CENTER = 90;
const int SWING_DEGREES = 12;        // slightly more movement looks better

const int MOVE_SPEED_MS = 8;         // ← ms per degree. 6-12 feels natural

const int DELAY_MIN = TEST_MODE ? 4000 : 8000;
const int DELAY_MAX = TEST_MODE ? 14000 : 22000;  // wider range feels more alive

const unsigned long RUN_TIME_MS = 2UL * 60 * 60 * 1000;  // 2 hours

// ====================== VARIABLES ======================
unsigned long startTime = 0;
bool running = true;

// ====================== HELPER ======================
void smoothMoveTo(int target) {
  if (!running) return;

  int current = myWheel.read();
  
  if (current < target) {
    for (int pos = current; pos <= target; pos++) {
      myWheel.write(pos);
      delay(MOVE_SPEED_MS);
    }
  } else {
    for (int pos = current; pos >= target; pos--) {
      myWheel.write(pos);
      delay(MOVE_SPEED_MS);
    }
  }
}

// ====================== SETUP ======================
void setup() {
  myWheel.attach(9);
  Serial.begin(115200);

  Serial.println("--- LEGO TESLA VOLUME KNOB STARTED ---");
  Serial.print("Will run for ");
  Serial.print(RUN_TIME_MS / 3600000);
  Serial.println(" hours");

  startTime = millis();

  // Gentle startup
  smoothMoveTo(CENTER);
  delay(300);
  smoothMoveTo(CENTER + SWING_DEGREES);
  delay(400);
  smoothMoveTo(CENTER - SWING_DEGREES);
  delay(400);
  smoothMoveTo(CENTER);

  Serial.println("Ready! 🎉");
}

// ====================== LOOP ======================
void loop() {
  // Time check
  if (running && (millis() - startTime >= RUN_TIME_MS)) {
    Serial.println("Run time finished. Shutting down...");
    for (int i = 0; i < 3; i++) {
      smoothMoveTo(CENTER + SWING_DEGREES);
      delay(400);
      smoothMoveTo(CENTER - SWING_DEGREES);
      delay(400);
    }
    smoothMoveTo(CENTER);
    myWheel.detach();           // important for battery life
    running = false;
  }

  if (!running) {
    delay(1000);
    return;
  }

  // === More natural behavior ===
  delay(random(DELAY_MIN, DELAY_MAX + 1));

  // Randomly choose direction and amount (more organic)
  int direction = random(0, 2) ? 1 : -1;
  int amount = random(6, SWING_DEGREES + 1);   // sometimes smaller swings
  smoothMoveTo(CENTER + direction * amount);
}