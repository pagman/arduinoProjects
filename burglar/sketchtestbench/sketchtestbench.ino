#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include "arduino_secrets.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <TelegramBot.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
int trigPin=4;
int echoPin=15;

uint16_t RECV_PIN = 13;
int piezoPin=5;
int pirState = LOW;
int ledGreen=14;
int ledRed=12;
int state;
int tele,ir;
int counter =0;
int distance;

IRrecv irrecv(RECV_PIN);

decode_results results;

char ssid[] = "GMANTAS";     // your network SSID (name)
char password[] = "O2O61961"; // your network key
String text;

// Initialize Telegram BOT
#define BOTtoken "568796039:AAF6mhReaEBuMBhB4vDBql0YvQDCZI5deMI"  // your Bot Token (Get from Botfather)

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done


void setup() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(piezoPin,OUTPUT);
  Serial.begin(115200);
  irrecv.enableIRIn();  // Start the receiver
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(RECV_PIN);
}

void loop() {
  long duration, distance;
  digitalWrite(piezoPin,LOW);
  int flag = 0;
  tele = readTele(flag);
//Serial.println("tele:");
//Serial.println(tele);
 ir=readIR();
//Serial.println(ir);
  /*while(ir==4){
  ir=readIR();}*/
  if ( ir==1 || tele==1)
    state=1;
  if ( ir==0 || tele==0)
    state=0;
//Serial.println("state:");
//Serial.println(state);   
 if (state==0){
  digitalWrite(ledGreen,HIGH);
  digitalWrite(ledRed,LOW);
  flag=0;
  }
if (state==1){
  pirState = LOW;
  digitalWrite(ledGreen,LOW);
  digitalWrite(ledRed,HIGH);
  flag = 0;
  tele = readTele(flag);
 // digitalWrite(ledRed,HIGH);
distance = distanceState(echoPin,trigPin);
Serial.println(distance);
  if (distance<50){
     //red led when motion detected
    while (state != 0){
      flag = 1;
      digitalWrite(piezoPin,HIGH);
      //tone(piezoPin, 1000);
      tele = readTele(flag);
      ir=readIR();
      while(ir==5){
      ir=readIR();}
        if ( ir==0 || tele==0){
          state=0;
          digitalWrite(ledRed,LOW);//off red led after disarming
          digitalWrite(piezoPin,LOW);
          pirState = LOW;          
          flag=0;
          tele = readTele(flag);
        }
          
    }
  }
  flag = 0;
}
  



}
int readIR (){
  int state;
  if (irrecv.decode(&results)) {
    //print() & println() can't handle printing long longs. (uint64_t)
    serialPrintUint64(results.value);
    Serial.println("");
    irrecv.resume();  // Receive the next value
    if ( results.value==16753245){
    Serial.println("armed");
    state=1;
    return state;    
  }
  if ( results.value==16769565){
    Serial.println("disarmed");
    state=0;
    return state;    
  }
  }
  
  return 4;   
}
int readTele (int flag){ //work perfect
  int state=3; 
  
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while(numNewMessages) {
      for (int i=0; i<numNewMessages; i++) {
       // bot.sendMessage(bot.messages[i].chat_id, bot.messages[i].text, "");
        text = bot.messages[i].text;
        //bot.sendMessage(bot.messages[i].chat_id, "text", "");
       if (text=="status"){
        if (flag==1)        
          bot.sendMessage(bot.messages[i].chat_id, "Burglar", "");
        if (flag==0)
          bot.sendMessage(bot.messages[i].chat_id, "Still Safe", "");}      
        if (text=="disarm")
        bot.sendMessage(bot.messages[i].chat_id, "System Disarmed", "");
        if (text=="arm")
        bot.sendMessage(bot.messages[i].chat_id, "System Armed", "");
        //bot.sendMessage(bot.messages[i].chat_id, "test", "");      
      }
     // Serial.println(text);
      if (text.equals("arm")) {
        Serial.println("armed");
        state=1;
        
      }
      if (text.equals("disarm")){
        Serial.println("disarmed");
        state=0;
      }
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }
  
  return state;
}

int distanceState (int echoPin , int trigPin){
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
 long duration = pulseIn(echoPin, HIGH);
 long distance = (duration/2) / 29.1;
  Serial.println("distanse:");
  Serial.print(distance);
  return distance;
}











