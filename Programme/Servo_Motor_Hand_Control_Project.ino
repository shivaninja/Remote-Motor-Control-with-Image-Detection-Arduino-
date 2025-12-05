#include <Servo.h>

Servo myServo;
int angle = 0;

void setup() {
  Serial.begin(9600);
  myServo.attach(9); // Servo signal pin to D9
  pinMode(13, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    angle = Serial.parseInt();  // Read angle from Python
    if (angle >= 0 && angle <= 180) {
      digitalWrite(13, HIGH);
      myServo.write(angle);
    }
  }
}
