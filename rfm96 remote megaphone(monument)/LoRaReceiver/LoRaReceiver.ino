#include <SPI.h>
#include <LoRa.h>
String message="";
void setup() {
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  while (!Serial);

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    //Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      
      
    //  Serial.print((char)LoRa.read());
      message.concat((char)LoRa.read());
      digitalWrite(LED_BUILTIN, HIGH);
    }
    Serial.println(message.indexOf("hello"));
    if ( message.indexOf("hello")==0){
    Serial.println("succes");
    digitalWrite(7, HIGH);
    delay(1000);
    }
    message = "";
    //Serial.print((char)LoRa.read());
    digitalWrite(7, LOW);
    // print RSSI of packet
    //Serial.print("' with RSSI ");
   // Serial.println(LoRa.packetRssi());
  }
}
