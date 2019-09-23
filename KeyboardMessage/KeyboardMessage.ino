/*
  Keyboard Message test

  For the Arduino Leonardo and Micro.

  Sends a text string when a button is pressed.

Arduino123!
  http://www.arduino.cc/en/Tutorial/KeyboardMessage
*/

#include "Keyboard.h"

const int buttonPin = 4;          // input pin for pushbutton
int previousButtonState = HIGH;   // button push counter
int x = 0;
void setup() {
  // initialize control over the keyboard:
  Keyboard.begin();
  
}

void loop() {
  while (x < 2){
    Keyboard.print("Arduino123!");
    Keyboard.write(176);
    delay(1000);
    x++;
}   
  
}
