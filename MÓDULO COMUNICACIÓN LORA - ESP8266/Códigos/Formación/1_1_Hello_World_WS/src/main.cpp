#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
// Replace with your network credentials
const char* ssid = "MiFibra-7D98";
const char* password = "NoVFC2RR";
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
void initWiFi() { /* Creamos funcion que inicia Wifi */
WiFi.mode(WIFI_STA); /* Configuramos el modo del ESP como una estación */
WiFi.begin(ssid, password); /* Decimos que se iniciará con la clave de nuestro wifi */
Serial.print("Connecting to WiFi .."); /* El mensaje que se imprime */
while (WiFi.status() != WL_CONNECTED) { /* Se ejecuta mientras el estado de wifi.status no sea wl_connected, que significa que la conexión wifi no se ha establecid.
Es decir, esta parte del código espera hasta que el ESP8266 se conecte exitosamente a la red Wi-Fi. */
Serial.print('.'); 
delay(1000); /* retraso de 1 seg para no saturar sistema con intentos de conexion muy rapidos */
}
Serial.println(WiFi.localIP()); /* imprime en el serial monitor la dirección IP asignada al ESP8266 después de que se haya conectado exitosamente a la red Wi-Fi */
}
void setup() {
// Serial port for debugging purposes
Serial.begin(115200); /* iniciamos el serial monitor a velocidad de 115200 */
delay(2000);
Serial.print("lo que quieras");
initWiFi(); /* llamamos a la funcion para iniciar wifi */
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
request->send(200, "text/html", index_html); /*esta sección del código configura un manejador para la ruta raíz ("/") que 
responderá con la página HTML almacenada en index_html cuando se realice una solicitud GET a esa ruta.*/
});
// Start server
server.begin();
}
void loop() {
}