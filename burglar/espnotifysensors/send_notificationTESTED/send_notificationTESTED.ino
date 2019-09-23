
#include <ESP8266WiFi.h>
#include <ESP_Notify.h>

// input your values here
//############################################################
#define WIFI_SSID     "GMANTAS"
#define WIFI_PASSWORD "O2O61961"

#define DEVICE_ID "f3TIhM0EVl0:APA91bFEhSm9dwBsxslSagtNjX4Tt6q0Hz6nKLDgB59uz8EE-jNYuoqADIaeGgtDDMCpaG_VPYjs1EcutFBwQxRIKTsBdaqPw1UcxtYQcMFiD9z76NDzmNjVl8UiWkV6Ci-RfIkKRWDz"
//############################################################

// define a notifier
ESP_Notify notifier;

void setup() {
  Serial.begin(115200);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("\n\nconnecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nconnected: ");
  Serial.println(WiFi.localIP());

  // Send notification
  notifier.sendNotification(DEVICE_ID, "Hello World!", "Stuff, Stuff!");
}

void loop() {
  //empty loop
}
