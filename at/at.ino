void setup() {
  // initialize D0 pin as an input:
  pinMode(0, INPUT);      
  // initialize D1 pin as an input:
  pinMode(1, INPUT); 
  Serial.write("AT");    
}
 
void loop(){
Serial.write("AT");
}
