#include <ESP8266WiFi.h>
#include "Adafruit_MQTT_Client.h"

#define Idr A0
#define wifi "AniRedmi"
#define password "12345678"
#define server "io.adafruit.com"
#define port 1883
#define username "ani979"
#define key "111f76fba8324f8c841d27a0488413c3"

WiFiClient wifiCl;

Adafruit_MQTT_Client mqtt(&wifiCl, server, port, username, key);
Adafruit_MQTT_Publish feed = Adafruit_MQTT_Publish(&mqtt, username"/feeds/LDR");


void setup() {
  // put your setup code here, to run once:
  Serial.begin(230400);
  delay(10);
  Serial.println("Adafruit MQTT demo");
  Serial.print("Connecting to ");
  Serial.println(wifi);

  WiFi.begin(wifi, password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Wifi connected ");
  Serial.print("IP Address: ");
  Serial.println(wifiCl.localIP());
  Serial.print("Connecting to MQTT");
  while(mqtt.connect()) {
    Serial.println(".");
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  if( mqtt.connected()) {
    int data =analogRead(Idr);
    Serial.println("Sending LDR val");
    Serial.print(data);
    Serial.print("...");
    if(feed.publish(data)) {
      Serial.println("Success");
    } else {
      Serial.println("Failure");
    }
    delay(1001);
  }
}
