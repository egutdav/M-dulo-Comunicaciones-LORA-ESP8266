#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "ESP8266AP";
const char* password = "digitalcodesign";

AsyncWebServer server(80);

IPAddress local_IP(192, 168, 1, 81); 
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);

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
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid, password);
}


void setup() {

  Serial.begin(115200);
  Serial.println("Iniciando ESP8266 como Access Point...");

  initAP();

  Serial.print("Iniciado AP ");
  Serial.println(ssid);
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  request->send(200, "text/html", index_html);
});

  server.begin();
}
void loop() {

}
