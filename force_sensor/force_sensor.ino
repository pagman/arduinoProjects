

#include <Servo.h>

Servo myservo;
int pressurePin = A0;
int force;
void setup() {
Serial.begin(9600);
}
void loop() {
  force = analogRead(pressurePin);
  //Serial.println(force);
  if ( force > 765){
    Serial.println("park available");
  }
  else {
    Serial.println("No parking");
  }
    delay(100);
}

