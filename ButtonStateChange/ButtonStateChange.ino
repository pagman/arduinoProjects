
const int buttonPin = 2;  
// variables will change:
int buttonState = 0;
int currentState = buttonState;
void setup() {
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  
  
  if (buttonState == HIGH) {
    currentState = !currentState;
    delay(300);
  } 
  Serial.println(currentState);
}
