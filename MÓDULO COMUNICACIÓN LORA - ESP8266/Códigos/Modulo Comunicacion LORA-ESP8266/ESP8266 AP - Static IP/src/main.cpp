#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <LittleFS.h>


const char* ssid = "ESP8266APpruebas";
const char* password = "digitalcodesign";

AsyncWebServer server(80);


IPAddress local_IP(192, 168, 1, 81); 
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

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
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid, password);
}


void setup() {

  Serial.begin(115200);
  Serial.println("Iniciando ESP8266 como Access Point...");

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
  Serial.println(F("No se pudo iniciar la pantalla OLED"));
  for(;;);
  }

  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Iniciando AP");
  display.display();


  initAP();
  initFS();

  display.clearDisplay();
  display.display();

  Serial.print("Iniciado AP ");
  Serial.println(ssid);
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());

  display.setCursor(0,0);
  display.println("SSID: " + String(ssid));
  display.println("IP: " + WiFi.softAPIP().toString());
  display.display();


  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  request->send(LittleFS, "/index.html", "text/html");
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
  request->send(LittleFS, "/style.css", "text/css");
  });
 
  server.begin();
  
}
void loop() {

}
