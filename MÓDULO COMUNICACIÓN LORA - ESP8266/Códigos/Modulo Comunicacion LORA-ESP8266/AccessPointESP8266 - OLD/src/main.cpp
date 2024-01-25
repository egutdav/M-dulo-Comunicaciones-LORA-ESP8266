#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

const char* ssid = "ESP8266Wifi";
const char* password = "digitalcodesign";

AsyncWebServer server(80);

void initFS() {
if (!LittleFS.begin()) {
Serial.println("An error has occurred while mounting LittleFS");
}
else{
Serial.println("LittleFS mounted successfully");
}

}

void initAP() {
WiFi.mode(WIFI_AP);
WiFi.softAP(ssid, password);
}

IPAddress local_IP(192, 168, 1, 84);

IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);

void setup() {

if(!WiFi.config(local_IP, gateway, subnet)) {
Serial.println("STA Failed to configure");
}
WiFi.begin(ssid, password);

Serial.begin(115200);

initAP();
initFS();
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
request->send(LittleFS, "/index.html", "text/html");
});
server.serveStatic("/", LittleFS, "/");


server.begin();
}
void loop() {

}