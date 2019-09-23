void setup() {
  Serial.begin(57600); 
}

void loop() {
  int avg = 0;
  for(int i=0;i<64;i++){
    avg+=analogRead(0);
  }
  Serial.println(avg/64);
  delay(5);
}
