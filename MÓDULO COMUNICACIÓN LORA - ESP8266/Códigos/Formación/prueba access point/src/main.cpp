#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
// Replace with desired access point credentials
const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<title>ESP Web Server</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
<style>
html {
font-family: Arial;
text-align: center;
}
body {
max-width: 400px;
margin:0px auto;
}
</style>
</head>
<body>
<h1>Hello World!</h1>
<p>Congratulations!<br>This is your first Web Server with the ESP.</p>
</body>
</html>
)rawliteral";
void initAP() {
WiFi.mode(WIFI_AP);
WiFi.softAP(ssid, password);
}

// Set your Static IP address
IPAddress local_IP(192, 168, 1, 80);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8); //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

void setup() {
// Serial port for debugging purposes
Serial.begin(115200);
initAP();
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
request->send(200, "text/html", index_html);
});
// Start server
server.begin();
}
void loop() {
// put your main code here, to run repeatedly:
}