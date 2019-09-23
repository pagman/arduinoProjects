#include <SoftwareSerial.h>

SoftwareSerial K02(6, 7); // RX, TX

void setup()
{
  Serial.begin(9600);
  K02.begin(9600);

}

void loop()
{ 
  delay(100);
  //mySerial.write(0xFF); //for mode 4
  while(K02.available())
  {
    if (K02.read() == 0xFF ) { //start
      while(K02.available()<3){};//wait for all data to be buffered
      uint8_t upper_data = K02.read();
      uint8_t lower_data = K02.read();
      uint8_t sum = K02.read();
      if (((upper_data + lower_data) & 0xff) == sum) {
        Serial.print(F("distance: "));
        uint16_t distance = (upper_data << 8) | (lower_data & 0xff);
        Serial.print(distance / 10);
        Serial.println(" cm");
      }
    }
  }
}
