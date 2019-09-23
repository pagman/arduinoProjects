   // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
 buttonState = digitalRead(2);
 Serial.println(buttonState);
  if (buttonState == HIGH) {
    // turn LED on:
   // digitalWrite(ledPin, HIGH);
  } else {
   // digitalWrite(ledPin, LOW);
  }
}
