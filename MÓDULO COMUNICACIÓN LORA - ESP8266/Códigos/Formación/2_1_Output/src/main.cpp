#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
// Replace with your network credentials
const char* ssid = "MiFibra-7D98";
const char* password = "NoVFC2RR";
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
// Set LED GPIO
const int ledPin = 2;
// Stores LED state
String ledState;
// Initialize LitleFS
void initFS() {
if (!LittleFS.begin()) {
Serial.println("An error has occurred while mounting LittleFS");
}
else{
Serial.println("LittleFS mounted successfully");
}
}
void initWiFi() {
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
Serial.print("Connecting to WiFi ..");
while (WiFi.status() != WL_CONNECTED) {
Serial.print('.');
delay(1000);
}
Serial.println(WiFi.localIP());
}
// Replaces placeholder with LED state value
String processor(const String& var) {
if(var == "STATE") {
if(digitalRead(ledPin)) {
ledState = "OFF";
}
else {
ledState = "ON";
}
return ledState;
}
return String();
}
void setup() {
Serial.begin(115200);
initWiFi();
initFS();
// Set GPIO2 as an OUTPUT
pinMode(ledPin, OUTPUT);
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
request->send(LittleFS, "/index.html", "text/html",false, processor);
});
server.serveStatic("/", LittleFS, "/");
// Route to set GPIO state to HIGH (inverted logic for ESP8266)
server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
digitalWrite(ledPin, LOW);
request->send(LittleFS, "/index.html", "text/html", false, processor);
});
// Route to set GPIO state to LOW (inverted logic for ESP8266)
server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
digitalWrite(ledPin, HIGH);
request->send(LittleFS, "/index.html", "text/html", false, processor);
});
server.begin();
}
void loop() {
}