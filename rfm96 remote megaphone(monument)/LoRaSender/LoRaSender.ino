#include <SPI.h>
#include <LoRa.h>

int counter = 0;

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();
  
}

void loop() {
 // int  trigger = analogRead(A0);
 // Serial.println(trigger);
 // if (trigger>1022){
  //Serial.print("Sending packet: ");
 // Serial.println(counter);

  // send packet
/*  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket(); */

 // counter++;

//  delay(5000);
 // }
}
