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

uint16_t RECV_PIN = 5;
int piezoPin=13;
int inputPin =4;
int pirState = LOW;
int ledGreen=14;
int ledRed=12;
int state;
int tele,ir;

IRrecv irrecv(RECV_PIN);

decode_results results;

// Initialize Wifi connection to the router
const char* ssid  = SECRET_SSID;
const char* password = SECRET_PASS;
const char BotToken[] = SECRET_BOT_TOKEN;
WiFiClientSecure net_ssl;
TelegramBot bot (BotToken, net_ssl);


void setup() {
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(inputPin, INPUT);
  Serial.begin(115200);
  irrecv.enableIRIn();  // Start the receiver
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(RECV_PIN);
  while (!Serial); // Wait for the Serial monitor to be opened

  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  bot.begin();

}

void loop() {
  tele = readTele();
  ir=readIR();
  while(ir==5){
  ir=readIR();}
  if ( ir==1 || tele==1)
    state=1;
  else
    state=0;
 Serial.println(state);   
 if (state==0){
  digitalWrite(ledGreen,HIGH);
  digitalWrite(ledRed,LOW);
  }
if (state==1){
  digitalWrite(ledGreen,LOW);
  digitalWrite(ledRed,HIGH);
  if (pirState==HIGH){
    while (state != 0){
      tone(piezoPin, 1000);
      tele = readTele();
      ir=readIR();
      while(ir=5){
      ir=readIR();}
        if ( ir==1 || tele==1)
          state=1;
        else
          state=0;
    }
  }
}
  







  
}
int readIR (){
  int state;
  if (irrecv.decode(&results)) {
    //print() & println() can't handle printing long longs. (uint64_t)
    serialPrintUint64(results.value);
    Serial.println("");
    irrecv.resume();  // Receive the next value
  }
  if ( results.value==16236607){
    state = 1;
    return state;
    Serial.println("succes");    
  }
  if (results.value==432838) {
    state=0;
    return state;
  }
  return 4;   
}
int readTele (){
  int state;
  message m = bot.getUpdates(); // Read new messages
  //Serial.println(m.text);
    if ( m.text == "arm" ){ // Checks if there are some updates
      state=1;
      //return state;
      //Serial.println(m.text);
      bot.sendMessage(m.chat_id, m.text);  // Reply to the same chat with the same !!text m.text saves the message you send!!
      return state;
    } 
    if (m.text == "disarm"){
      state=0;
      //m.text="no new message";
      //Serial.println("no new message");
      bot.sendMessage(m.chat_id, m.text);
      return state;
    }
    return 5;
}










