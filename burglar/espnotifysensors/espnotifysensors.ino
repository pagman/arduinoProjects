
#include <ESP8266WiFi.h>
#include <ESP_Notify.h>

// define your values here
//############################################################
#define WIFI_SSID     "AAABBB"
#define WIFI_PASSWORD "SUCKYOURASS"
/*const int trigPin =16;
const int echoPin =5;
long duration;
int distance;
*/
#define DEVICE_ID "cnfsleo6T8c:APA91bHVsTOsEiWU_eFwqysv_tfbcCk0B4LPyjdbO4kyKHl2_ybhif8xzPSYvW9oezg88qlWO4ICDo2hxvEvvTw3uAG4glMeH6HsWg-maq8Jy8vviTknGFfCx--60fvDSKomBDDBR3LI"
//############################################################

ESP_Notify notifier;
int LED = 2; //D4
int PIR = 4; //D2
int irpin=0; //D3
int interval = 5000;
int previous_millis = millis();
boolean state = LOW;
boolean newState = LOW;


void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(PIR, INPUT);
//  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  //pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(irpin,OUTPUT);
  digitalWrite(irpin,LOW);
  
  //calling the connectToWifi() function
  connectToWifi();
}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    connectToWifi();        //reconnect in case of connection loss
  }
  update();
//  ultra();
 // irsensor();
}


void connectToWifi(){
  // funtion to connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("\n\nconnecting");
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED, !digitalRead(LED));   // blink internal LED
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nconnected: ");
  Serial.println(WiFi.localIP());
  digitalWrite(LED, HIGH);
}

void update(){
  newState = digitalRead(PIR);
  if (newState != state) {
    if(newState){
      // sending Notification
      Serial.println("Movement started!");
      notifier.sendNotification(DEVICE_ID, "Alarm!", "Movement in the room!");
      digitalWrite(LED, LOW);
    }else{
      // sending Notification
      Serial.println("Movement stopped!");
      notifier.sendNotification(DEVICE_ID, "Alarm!", "Movement has stopped!");
    digitalWrite(LED, HIGH);
    }
    state = newState;
  }
}
/*
void ultra(){
  // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
if(distance<20)
{
  notifier.sendNotification(DEVICE_ID, "Alarm!", "Water level critical!!");
delay(200);
}
else
delay(100);
}
*/
/*void irsensor(){
  if(irpin==HIGH)
  notifier.sendNotification(DEVICE_ID, "Alarm!", "Door open!");
  else
  delay(100);
}
*/
