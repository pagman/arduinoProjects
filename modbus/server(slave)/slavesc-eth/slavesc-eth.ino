#include <SPI.h>
#include <Ethernet.h> // for MKR WiFi 1010
// #include <WiFi101.h> // for MKR1000

#include <ArduinoRS485.h> 
#include <ArduinoModbus.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 0, 177);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(502);


ModbusTCPServer modbusTCPServer;
const int button1Pin = 2;
const int button2Pin = 3;  
int ledPin1 = 13;
int ledPin2 = 14;
int button1State = 0;
int button2State = 0;
int current1State = button1State;
int current2State = button2State;

void setup() {
  Ethernet.init(5);
  Ethernet.begin(mac, ip);
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); 
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  //Initialize serial and wait for port to open:
  Serial.begin(9600);
//  while (!Serial) {
//    ; 
//  }

  Serial.print(ip);
  Serial.println(" port: 502");



  // start the Modbus TCP server
  if (!modbusTCPServer.begin()) {
    Serial.println("Failed to start Modbus TCP Server!");
    while (1);
  }


  // configure a single coil at address 0x00
  modbusTCPServer.configureCoils(0x02, 4);
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {

  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  
  if (button1State == HIGH) {
    current1State = !current1State;
    Serial.print("button 1 :");
    Serial.println(current1State);
    delay(300);
  } 
  if (button2State == HIGH) {
    current2State = !current2State;
    Serial.print("button 2:");
    Serial.println(current2State);
    delay(300);
  }
    modbusTCPServer.coilWrite(0x02,  current1State);
    modbusTCPServer.coilWrite(0x03,  current2State);
  
  // listen for incoming clients
  EthernetClient client = server.available();

  if (client) {
    // a new client connected
    Serial.println("new client");

    // let the Modbus TCP accept the connection
    modbusTCPServer.accept(client);
    // poll for Modbus TCP requests, while client connected
    modbusTCPServer.poll();
    modbusTCPServer.coilWrite(0x02,  current1State);
    modbusTCPServer.coilWrite(0x03,  current2State);
    modbusTCPServer.poll();
    int a = modbusTCPServer.coilRead(0x04);
    int b = modbusTCPServer.coilRead(0x05);
    Serial.println("0x04 value : ");
    Serial.println(a);
    Serial.println("0x05 value : ");
    Serial.println(b);
    
    delay(1000);
    Serial.println("client disconnected");

    
    if (a == 1) {
    // turn LED on:
    digitalWrite(ledPin1, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin1, LOW);
  }

  
  if (b == 1) {
    // turn LED on:
    digitalWrite(ledPin2, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin2, LOW);
  }
  }
}
