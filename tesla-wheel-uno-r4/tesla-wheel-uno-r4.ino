#include <Servo.h>

Servo myWheel;

// ====================== SETTINGS ======================
const int CENTER = 90;           // Middle position for the knob
const int ANGLE_OFFSET = 10;     // How far left/right it swings

const int STEP_DELAY = 10;       // Speed of movement (ms per degree). Higher = slower & smoother

const int DELAY_MIN = 9000;      // Minimum pause between sweeps (7 seconds)
const int DELAY_MAX = 17000;     // Maximum pause between sweeps (17 seconds)

// How long the whole thing runs before stopping
const unsigned long RUN_TIME_MS = 3UL * 60 * 60 * 1000;  // 3 hours

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
      delay(STEP_DELAY);
    }
  } else {
    for (int pos = current; pos >= target; pos--) {
      myWheel.write(pos);
      delay(STEP_DELAY);
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
  sweepTo(CENTER + ANGLE_OFFSET);
  delay(300);
  sweepTo(CENTER - ANGLE_OFFSET);
  delay(300);

  Serial.println("Ready to go! 🎉");
}


// ====================== MAIN LOOP ======================
void loop() {
  
  // === Time check: Should we stop? ===
  if (running && (millis() - startTime >= RUN_TIME_MS)) {
    Serial.println("3 hours are up! Stopping now to save battery.");
    myWheel.write(CENTER);       // Go back to middle
    delay(500);
    myWheel.detach();            // This saves the most power
    running = false;
  }

  // If we're done, just chill
  if (!running) {
    delay(1000);
    return;
  }

  // === Normal dancing ===
  delay(random(DELAY_MIN, DELAY_MAX + 1));   // Random pause
  sweepTo(CENTER + ANGLE_OFFSET);            // Turn right

  delay(random(DELAY_MIN, DELAY_MAX + 1));   // Another random pause
  sweepTo(CENTER - ANGLE_OFFSET);            // Turn left
}