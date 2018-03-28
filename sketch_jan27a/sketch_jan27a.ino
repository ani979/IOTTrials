#include <ESP8266WebServer.h>

ESP8266WebServer server;

const char username[] = "ANIIOT";
const char password[] = "12345678";
#define pin 16
void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  pinMode(pin, OUTPUT);
  WiFi.softAP(username, password);
  IPAddress ipaddr = WiFi.softAPIP();
  //Serial.println("IP Address is " + ipaddr);
  server.begin();
  server.on("/led", led);
  //String stripaddr = "IP Address is " + ipaddr;
  
  Serial.println("IP Address is ");
  Serial.println(ipaddr);

}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(pin, LOW);
  //delay(5000);
  //digitalWrite(pin, HIGH);
  //delay(5000);
  //Serial.println("LED ON");
  server.handleClient();
}

void led() {
  String myhtml = "<html><head><title> IOT Workshop </title></head><body style = background-color:palegreen><h1> <center> IOT </center></h1> <form> <br> <button name = \"pin\" type = \"submit\" value = \"0\"> LED ON </button> <button name = \"pin\" type = \"submit\" value = \"1\"> LED OFF </button> <button name = \"pin\" type = \"submit\" value = \"2\"> BLINK </button></form></body></html>";
  server.send(200, "text/html", myhtml);
  
  if(server.arg("pin") == "1") {
    digitalWrite(pin, HIGH);
  } else if(server.arg("pin") == "0") {
    digitalWrite(pin, LOW);
  } else {
    int i = 0;
    while(i < 10) {
      digitalWrite(pin, HIGH);
      delay(1000);
      digitalWrite(pin, LOW);
      Serial.print("Hello...");
      i++;
    }
  }
} 


