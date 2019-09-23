/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;
int joyX = A0;
int x ;
int force;// variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
     x = analogRead(joyX);
     force = analogRead(joyX);
    Serial.println(force);
  x = map(analogRead(joyX), 10, 259, 0, 180);
  myservo.write(x);
}

