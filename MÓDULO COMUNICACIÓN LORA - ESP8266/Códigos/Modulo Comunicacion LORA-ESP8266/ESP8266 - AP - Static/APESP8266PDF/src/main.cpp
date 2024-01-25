#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "PruebaGPT";
const char* password = "digitalcodesign";

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

void setupAP() {
  // Configura el ESP8266 en modo AP
  WiFi.mode(WIFI_AP);
  
  // Configura el Access Point con una dirección IP estática
  IPAddress local_IP(192, 168, 1, 81);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);

  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid, password);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando ESP8266 como Access Point...");

  // Configura el ESP8266 como Access Point
  setupAP();

  Serial.print("IP address del Access Point:\t");
  Serial.println(WiFi.softAPIP());

  // Configura rutas para el servidor web
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", index_html);
  });

  // Inicia el servidor web
  server.begin();
}

void loop() {
  // El bucle principal, por el momento está vacío
}
