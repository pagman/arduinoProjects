// Adafruit IO REST API access with ESP8266
//
// For use with ESP8266 Arduino from:
//   https://github.com/esp8266/Arduino
//
// Works great with ESP8266 modules like the Adafruit Huzzah ESP:
//  ----> https://www.adafruit.com/product/2471
//
// Written by Tony DiCola for Adafruit Industries.  
// MIT license, all text above must be included in any redistribution.
#include <ESP8266WiFi.h>
#include "Adafruit_IO_Client.h"


// Configure WiFi access point details.
#define WLAN_SSID  "GMANTAS"
#define WLAN_PASS  "O2O61961"

// Configure Adafruit IO access.
#define AIO_KEY    "0cead6f2b9d84f3bab1d463b2fb43cc7"
int forceSensor = 0;
int force;
int sensor1 = 16;
int sensor2 = 5;
int sensor3 = 4;
int sensor4 = 2;
// Create an ESP8266 WiFiClient class to connect to the AIO server.
WiFiClient client;

// Create an Adafruit IO Client instance.  Notice that this needs to take a
// WiFiClient object as the first parameter, and as the second parameter a
// default Adafruit IO key to use when accessing feeds (however each feed can
// override this default key value if required, see further below).
Adafruit_IO_Client aio = Adafruit_IO_Client(client, AIO_KEY);

// Finally create instances of Adafruit_IO_Feed objects, one per feed.  Do this
// by calling the getFeed function on the Adafruit_IO_FONA object and passing
// it at least the name of the feed, and optionally a specific AIO key to use
// when accessing the feed (the default is to use the key set on the
// Adafruit_IO_Client class).
Adafruit_IO_Feed testFeed1 = aio.getFeed("PatissionParking1");
Adafruit_IO_Feed testFeed2 = aio.getFeed("PatissionParking2");
Adafruit_IO_Feed testFeed3 = aio.getFeed("PatissionParking3");
Adafruit_IO_Feed testFeed4 = aio.getFeed("PatissionParking4");

// Alternatively to access a feed with a specific key:
//Adafruit_IO_Feed testFeed = aio.getFeed("esptestfeed", "...esptestfeed key...");

// Global state to increment a number and send it to the feed.
unsigned int count = 0;

void setup() {
  // Setup serial port access.
  Serial.begin(9600);
  delay(10);
  Serial.println(); Serial.println();
  Serial.println(F("Adafruit IO ESP8266 test!"));

  // Connect to WiFi access point.
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");  
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  
  // Initialize the Adafruit IO client class (not strictly necessary with the
  // client class, but good practice).
  aio.begin();

  Serial.println(F("Ready!"));
  pinMode(sensor1 , OUTPUT);
  pinMode(sensor2 , OUTPUT);
  pinMode(sensor3 , OUTPUT);
  pinMode(sensor4 , OUTPUT);
}

void loop() {
  
    digitalWrite(sensor1,HIGH);
    digitalWrite(sensor2,LOW);
    digitalWrite(sensor3,LOW);
    digitalWrite(sensor4,LOW);
  force = analogRead(forceSensor);
  testFeed1.send(force);
   if (force > 850){
    testFeed1.send("Park Available");
    Serial.print("sensor1");
    Serial.print(force);
 }
  else {
   testFeed1.send("No parking");
  }
  digitalWrite(sensor1,LOW);
  digitalWrite(sensor2,HIGH);
  digitalWrite(sensor3,LOW);
  digitalWrite(sensor4,LOW);
  force =  analogRead(forceSensor);
  testFeed2.send(force);
   if (force > 850){
    testFeed2.send("Park Available");
    Serial.print("sensor2");
    Serial.print(force);
   }
   else {
    testFeed2.send("No Parking");
   }
   digitalWrite(sensor1,LOW);
   digitalWrite(sensor2,LOW);
   digitalWrite(sensor3,HIGH);
   digitalWrite(sensor4,LOW);
   force =  analogRead(forceSensor);
   testFeed3.send(force);
   if (force > 850){
    testFeed3.send("Park Available");
    Serial.print("sensor3");
    Serial.print(force);
   }
   else {
    testFeed3.send("No Parking");
   }
   digitalWrite(sensor1,LOW);
   digitalWrite(sensor2,LOW);
   digitalWrite(sensor3,LOW);
   digitalWrite(sensor4,HIGH);
   force =  analogRead(forceSensor);
   testFeed4.send(force);
   if (force > 850){
    testFeed4.send("Park Available");
    Serial.print("sensor4");
    Serial.print(force);
   }
   else {
    testFeed4.send("No Parking");
   }
   digitalWrite(sensor1,LOW);
   digitalWrite(sensor2,LOW);
   digitalWrite(sensor3,LOW);
   digitalWrite(sensor4,LOW);

  
  delay(1000);
}
