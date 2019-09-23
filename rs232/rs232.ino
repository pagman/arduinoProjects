
int led = 13;
void setup()
{
  Serial.begin(9600);
  //pinMode(led,OUTPUT);
}
void loop()
{
  int temp;
    temp=Serial.read();
    // if(temp=='V'){
     // digitalWrite();
     //Serial.write((char)65);
    // Serial.print("dokimastiko");
    // Serial.print(123);
     Serial.print(analogRead(0));
     Serial.print('\n');
   // Serial.println(1);
     
 delay(500);
}
