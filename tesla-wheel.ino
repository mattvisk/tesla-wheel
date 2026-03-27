// Arduino Uno R4 WiFi - Random motor spin
// Spins immediately on start, then waits randomly 20–40 seconds between spins
// Spin duration: randomly 1–4 seconds with PWM fluctuation

const int motorPin = 9; // PWM pin (good for speed control)

unsigned long previousMillis = 0;
unsigned long waitTime = 0;       // random wait time between spins (ms)
unsigned long runDuration = 0;    // random spin duration (ms)

bool motorRunning = false;
unsigned long motorStartTime = 0;
unsigned long lastFluctuationMillis = 0;

void startMotor() {
  motorRunning = true;
  motorStartTime = millis();
  lastFluctuationMillis = millis();
  runDuration = random(1000, 4001); // 1 to 4 seconds
  analogWrite(motorPin, 255);
}

void setup() {
  pinMode(motorPin, OUTPUT);
  Serial.begin(115200);
  randomSeed(analogRead(0)); // improve randomness

  // Spin immediately on start
  startMotor();
  Serial.println("-> Motor ON (startup)");

  // Set wait time for after this first spin
  waitTime = random(20000, 40001);
}

void loop() {
  unsigned long currentMillis = millis();

  if (!motorRunning) {
    // === WAITING PHASE ===
    if (currentMillis - previousMillis >= waitTime) {
      startMotor();
      Serial.println("-> Motor ON");

      // Choose NEW random wait time for next cycle (20–40 seconds)
      waitTime = random(20000, 40001);
      previousMillis = currentMillis;
    }
  }
  else {
    // === MOTOR RUNNING PHASE ===

    // Fluctuate PWM every 80ms for organic speed variation (200–255 range)
    if (currentMillis - lastFluctuationMillis >= 80) {
      analogWrite(motorPin, random(200, 256));
      lastFluctuationMillis = currentMillis;
    }

    if (currentMillis - motorStartTime >= runDuration) {
      // Stop the motor
      analogWrite(motorPin, 0);
      motorRunning = false;
      previousMillis = currentMillis;

      Serial.print("<- Motor OFF after ");
      Serial.print(runDuration / 1000.0, 3);
      Serial.println(" seconds");

      Serial.print("Next spin in ~");
      Serial.print(waitTime / 1000.0, 1);
      Serial.println(" seconds");
    }
  }
}
