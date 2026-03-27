// Arduino Uno R4 WiFi - Random motor spin
// Spins immediately on start, then waits randomly 20–40 seconds between spins
// Spin duration: randomly 0.25–1.12 seconds

const int motorPin = 9; // PWM pin (good for speed control)

unsigned long previousMillis = 0;
unsigned long waitTime = 0; // random wait time between spins (ms)

bool motorRunning = false;
unsigned long motorStartTime = 0;

void setup() {
  pinMode(motorPin, OUTPUT);
  Serial.begin(115200);
  randomSeed(analogRead(0)); // improve randomness

  // Spin immediately on start
  motorRunning = true;
  motorStartTime = millis();
  analogWrite(motorPin, 255);
  Serial.println("-> Motor ON (startup)");

  // Set wait time for after this first spin
  waitTime = random(20000, 40001);
}

void loop() {
  unsigned long currentMillis = millis();

  if (!motorRunning) {
    // === WAITING PHASE ===
    if (currentMillis - previousMillis >= waitTime) {
      // Time to spin!
      motorRunning = true;
      motorStartTime = currentMillis;

      // Spin at full speed (change 255 to lower value for slower spin)
      analogWrite(motorPin, 255);

      Serial.println("-> Motor ON");

      // Choose NEW random wait time for next cycle (20-40 seconds)
      waitTime = random(20000, 40001);
      previousMillis = currentMillis;
    }
  }
  else {
    // === MOTOR RUNNING PHASE ===
    // Random spin duration between 0.25s and 1.12s
    unsigned long runDuration = random(250, 1121); // 250ms to 1120ms

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
