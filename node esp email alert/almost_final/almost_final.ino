#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <rBase64.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
byte sendEmail(int x);
byte eRcv(WiFiClientSecure client);


//define your default values here, if there are different values in config.json, they are overwritten.
char mqtt_server[40] = "login mail";
char mqtt_port[17] = "login pass";
char blynk_token[34] = "mail to";
char blynk_token1[34] = "message here";//add field here<------------------------------------------------
 int  buttonPin = 0;


int buttonState = 0; 
//flag for saving data
bool shouldSaveConfig = false;

//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}
rBase64generic<250> mybase1;
rBase64generic<250> mybase2;

void setup() {
  pinMode(A0, INPUT);
  
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();

  //clean FS, for testing
  //SPIFFS.format();

  //read configuration from FS json
  Serial.println("mounting FS...");

  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          Serial.println("\nparsed json");

          strcpy(mqtt_server, json["mqtt_server"]);
          strcpy(mqtt_port, json["mqtt_port"]);
          strcpy(blynk_token, json["blynk_token"]);
          strcpy(blynk_token1, json["blynk_token1"]);//add the same field here<---------------------------------------------

        } else {
          Serial.println("failed to load json config");
        }
        configFile.close();
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
  //end read



  // The extra parameters to be configured (can be either global or just in the setup)
  // After connecting, parameter.getValue() will get you the configured value
  // id/name placeholder/prompt default length
  WiFiManagerParameter custom_mqtt_server("server", "login mail", mqtt_server, 40);
  WiFiManagerParameter custom_mqtt_port("port", "login pass", mqtt_port, 17);
  WiFiManagerParameter custom_blynk_token("blynk", "mail to", blynk_token, 32);
  WiFiManagerParameter custom_blynk_token1("blynk1", "message here", blynk_token1, 34);//add the field also here again <-----------------------------------

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  //set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  //set static ip
  //wifiManager.setSTAStaticIPConfig(IPAddress(10,0,1,99), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
  
  //add all your parameters here
  wifiManager.addParameter(&custom_mqtt_server);
  wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.addParameter(&custom_blynk_token);
  wifiManager.addParameter(&custom_blynk_token1);//one more time here and we are done<---------------------------------------

  //reset settings - for testing
  //wifiManager.resetSettings();

  //set minimu quality of signal so it ignores AP's under that quality
  //defaults to 8%
  //wifiManager.setMinimumSignalQuality();
  
  //sets timeout until configuration portal gets turned off
  //useful to make it all retry or go to sleep
  //in seconds
  //wifiManager.setTimeout(120);
   
  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect("EmailOfThings", "password");
  /*if (!wifiManager.autoConnect("EmailOfThings", "password")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  }*/

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");

  //read updated parameters
  strcpy(mqtt_server, custom_mqtt_server.getValue());
  strcpy(mqtt_port, custom_mqtt_port.getValue());
  strcpy(blynk_token, custom_blynk_token.getValue());
  strcpy(blynk_token1, custom_blynk_token1.getValue());//aaadn here <-----------------------------------

  //save the custom parameters to FS
  if (shouldSaveConfig) {
    Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["mqtt_server"] = mqtt_server;
    json["mqtt_port"] = mqtt_port;
    json["blynk_token"] = blynk_token;
    json["blynk_token1"] = blynk_token1;//add for the last time here <----------------------------------

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
    //end save
  }

  Serial.println("local ip");
  Serial.println(WiFi.localIP());


//MAIL SETUP-------------------------------------

Serial.begin(115200);
  delay(10);
  Serial.println("");
  Serial.print("Connecting To ");
 /* WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());*/

    
 
mybase1.encode(mqtt_server);
mybase2.encode(mqtt_port);


}

/*const char* SSID = "HellasDigital"; 
const char* PASS = "asd123!!"; */



const char* user_base64 = mybase1.result();; // https://www.base64encode.org/
const char* user_password_base64 = mybase2.result();; 
const char* from_email = "MAIL From: <hellasdigital8080@gmail.com>"; 
const char* to_email = "RCPT TO: <p.mantas@hellasdigital.gr>"; 



void loop() {
 
// buttonState = analogRead(A0);
 //Serial.println("haaaaaaaaaaaaaaaaaaaaaaaaa");
 Serial.println(analogRead(A0));
 //digitalWrite(buttonPin, LOW);
 if (analogRead(A0) > 1000) {
 int sensorValue = analogRead(1);

//Serial.println(user);
//Serial.println(pass);
Serial.println(mqtt_server);
Serial.println(mqtt_port);
Serial.println(blynk_token);
  Serial.println(blynk_token1);
  
  //if(sensorValue <100){
       if (sendEmail(sensorValue)) Serial.println(F("Email sent"));
       else Serial.println(F("Email failed"));
  //}
  delay(10000);
  //digitalWrite(buttonPin, LOW);
 }

}

byte sendEmail(int x) 
{
  WiFiClientSecure client;
  if (client.connect("smtp.gmail.com", 465) == 1) Serial.println(F("connected"));
  else {   Serial.println(F("connection failed"));   return 0; }
  
  if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending EHLO")); client.println("EHLO 1.2.3.4"); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending login")); client.println("AUTH LOGIN"); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending User base64")); client.println(user_base64); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending Password base64")); client.println(user_password_base64); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending From")); client.println(from_email); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending To")); client.println(to_email); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending DATA")); client.println(F("DATA")); if (!eRcv(client)) return 0;
  client.println(F("Subject: E-mail Alert\r\n"));
  client.println(blynk_token1);
  //client.println(x);
  client.println(F("."));
  if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending QUIT"));
  client.println(F("QUIT"));
  if (!eRcv(client)) return 0;
  client.stop();
  return 1;
}

byte eRcv(WiFiClientSecure client)
{
  byte respCode;
  byte thisByte;
  int loopCount = 0;

  while (!client.available()) {
    delay(1);
    loopCount++;
    if (loopCount > 10000) {
      client.stop();
      Serial.println(F("\r\nTimeout"));
      return 0;
    }
  }

  respCode = client.peek();
  while (client.available())
  {
    thisByte = client.read();
    Serial.write(thisByte);
  }
  if (respCode >= '4')return 0;
  return 1;
  delay(10000);
}
