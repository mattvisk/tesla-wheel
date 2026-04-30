#include <Servo.h>

Servo myWheel;

// ====================== SETTINGS ======================
const bool TEST_MODE = false;    // Set to true to halve delays for faster testing

const int CENTER = 90;           // Middle position for the knob
const int SWING_DEGREES = 10;    // How many degrees left/right it turns from center

const int MS_PER_DEGREE = 0;    // How long to pause between each degree of movement. Higher = slower

const int DELAY_MIN = TEST_MODE ? 9000 / 2 : 9000;
const int DELAY_MAX = TEST_MODE ? 17000 / 2 : 17000;

// How long the whole thing runs before stopping
const unsigned long RUN_TIME_MS = 2UL * 60 * 60 * 1000;  // 2 hours

// ====================== VARIABLES ======================
unsigned long startTime = 0;     // When the program started
bool running = true;             // Keeps track if we're still supposed to move


// ====================== HELPER FUNCTIONS ======================
void sweepTo(int target) {
  if (!running) return;          // Don't move if time is up
  
  int current = myWheel.read();  // Where is the servo right now?
  
  // Smoothly move to the target position
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
}


// ====================== SETUP ======================
void setup() {
  myWheel.attach(9);             // Plug the servo into pin 9
  Serial.begin(115200);

  Serial.println("--- LEGO TESLA VOLUME KNOB STARTED ---");
  Serial.println("It will run for 3 hours then stop to save battery.");

  startTime = millis();          // Remember when we started

  // Slow startup wiggle from known center position
  sweepTo(CENTER + SWING_DEGREES);
  delay(300);
  sweepTo(CENTER - SWING_DEGREES);
  delay(300);

  Serial.println("Ready to go! 🎉");
}


// ====================== MAIN LOOP ======================
void loop() {
  
  // === Time check: Should we stop? ===
  if (running && (millis() - startTime >= RUN_TIME_MS)) {
    Serial.println("1 hour is up! Signing off...");
    // 3 goodbye movements, half a second apart
    for (int i = 0; i < 3; i++) {
      myWheel.write(CENTER + SWING_DEGREES);
      delay(500);
      myWheel.write(CENTER - SWING_DEGREES);
      delay(500);
    }
    myWheel.write(CENTER);       // Park in the middle
    delay(500);
    myWheel.detach();            // Save power
    running = false;
  }

  // If we're done, just chill
  if (!running) {
    delay(1000);
    return;
  }

  // === Normal dancing ===
  delay(random(DELAY_MIN, DELAY_MAX + 1));   // Random pause
  sweepTo(CENTER + SWING_DEGREES);            // Turn right

  delay(random(DELAY_MIN, DELAY_MAX + 1));   // Another random pause
  sweepTo(CENTER - SWING_DEGREES);            // Turn left
}