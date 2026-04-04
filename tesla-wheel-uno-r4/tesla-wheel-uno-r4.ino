#include <Servo.h>

Servo myWheel;

void setup() {
  myWheel.attach(9);
  Serial.begin(115200);

  Serial.println("--- LEGO TESLA VOLUME KNOB STARTED ---");

  // === Simple startup movement to ensure it's working ===
  myWheel.write(90);    // Start at center
  delay(500);
  
  myWheel.write(112);   // Move to +22°
  delay(800);
  
  myWheel.write(90);    // Back to center
  delay(800);

  Serial.println("Startup done - now running continuously");
}

void loop() {

  myWheel.write(112);   // +22°
  Serial.println(">> +22°");
  delay(random(7000, 17001));

  myWheel.write(68);    // -22°
  Serial.println(">> -22°");
  delay(random(7000, 17001));

}