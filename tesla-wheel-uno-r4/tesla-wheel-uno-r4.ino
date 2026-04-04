#include <Servo.h>

Servo myWheel;

void setup() {
  myWheel.attach(9);        // Servo signal on pin 9
  Serial.begin(115200);

  Serial.println("--- TESLA WHEEL STARTING ---");
  
  // Gentle startup to center
  myWheel.write(90);
  delay(800);

  Serial.println("Program started - oscillating ±22°");
}

void loop() {
  // === Move to +22° ===
  myWheel.write(112);        // 90 + 22
  Serial.println(">> Servo moved to +22°");
  
  long wait1 = random(7000, 17001);   // 7 to 17 seconds
  Serial.print("Waiting ");
  Serial.print(wait1 / 1000);
  Serial.println(" seconds...");
  delay(wait1);

  // === Move to -22° ===
  myWheel.write(68);         // 90 - 22
  Serial.println(">> Servo moved to -22°");
  
  long wait2 = random(7000, 17001);   // 7 to 17 seconds
  Serial.print("Waiting ");
  Serial.print(wait2 / 1000);
  Serial.println(" seconds...");
  delay(wait2);

  Serial.println("-------------------------");
}