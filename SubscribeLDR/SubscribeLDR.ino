#include <ESP8266WiFi.h>
#include "Adafruit_MQTT_Client.h"

#define Idr A0
#define wifi "AniRedmi"
#define password "12345678"
#define server "io.adafruit.com"
#define port 1883
#define username "ani979"
#define key "111f76fba8324f8c841d27a0488413c3"
#define pin 16
bool continueBlink = true;

WiFiClient wifiCl;

Adafruit_MQTT_Client mqtt(&wifiCl, server, port, username, key);
Adafruit_MQTT_Subscribe feed = Adafruit_MQTT_Subscribe(&mqtt, username"/feeds/LDR");


void setup() {
  // put your setup code here, to run once:
  Serial.begin(230400);
  pinMode(pin, OUTPUT);
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
  mqtt.subscribe(&feed);
  while(mqtt.connect()) {
    delay(500);
    Serial.println(".");
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  //continueBlink = false;
  if( mqtt.readSubscription(5000)) {
    Serial.println("Got:  ");
    Serial.print((char *)feed.lastread);
    int a = atoi((char *)feed.lastread); 
    Serial.print(" ");
    Serial.println(a);
    if(a==0) {
      continueBlink = false;
      digitalWrite(pin, LOW);
    } else if (a == 1){
      continueBlink = false;
      digitalWrite(pin, HIGH);
    } else if (a == 3) {
      continueBlink = true;
      Serial.print(" Is blink to be done : ");
      Serial.print(continueBlink);
      
    }
  }
  blink();
}

void blink() {
  if (continueBlink) {
    Serial.print(" Blinking ");
    digitalWrite(pin, LOW);
    delay(1000);
    digitalWrite(pin, HIGH);
    delay(1000);
    Serial.println("LED BLINKING");
  }
}

