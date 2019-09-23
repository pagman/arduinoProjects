#include <SPI.h>
#include <LoRa.h>

void setup() {
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  //pinMode(LED_BUILTIN, OUTPUT);
  while (!Serial);

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  digitalWrite(7, HIGH);
      delay(1000);
 digitalWrite(7, LOW); 
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      
      digitalWrite(7, HIGH);
      delay(300);
      Serial.print((char)LoRa.read());
      digitalWrite(LED_BUILTIN, HIGH);
    }
   // 
    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
  digitalWrite(7, LOW);
}
