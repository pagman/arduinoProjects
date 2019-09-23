#include <SPI.h>
#include <LoRa.h>

int counter = 0;
const int buttonPin = 7;
int buttonState = 0;

void setup() {
   pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == HIGH){
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(5000);
  }
  else
  Serial.println("unpressed");
}
