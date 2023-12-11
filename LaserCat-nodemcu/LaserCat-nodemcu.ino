#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

SoftwareSerial nodemcu_softSerial (D1,D2); //TX, RX

// const char *ssid = "Telecentro-f8e3"; // Reemplaza con el nombre de tu red WiFi
// const char *password = "Valen.2020"; // Reemplaza con la contraseña de tu red WiFi

const char *ssid_ap = "CatBot-wifi";    // Nombre de la red WiFi
const char *password_ap = "34815980"; // Contraseña de la red WiFi

IPAddress local_IP(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

void setup() {
  nodemcu_softSerial.begin(9600);
  Serial.begin(115200);
  Serial.println();

  Serial.print("Setting soft-AP ip configuration ... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

  Serial.print("Setting soft-AP ssid ... ");
  Serial.println(WiFi.softAP(ssid_ap,ssid_ap) ? "Ready" : "Failed!");

  Serial.print("Soft-AP IP address: ");
  Serial.println(WiFi.softAPIP());


  // Configura el modo de estación (STA) para conectarse a la red WiFi
  // WiFi.mode(WIFI_AP);
  
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.println("Conectando a WiFi...");
  // }

  while(!WiFi.softAP(ssid_ap, password_ap))
  {
    Serial.println(".");
    delay(100);
  }

  // Serial.println("Conexión exitosa a WiFi");
  Serial.println("WiFi emitiendo");
  Serial.println(ssid_ap);
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());


  //Serial.println(WiFi.localIP().toString());

  /*WEBSERVER*/

  // server.on("/", [](){
  //   server.send(200, "application/", "POST /config/laser - Enciend/apaga laser\n
  //   POST /config/autoplay - Enciende/apaga autoplay\n
  //   POST /config/autoplay ");
  // });

  server.on("/config/laser", HTTP_POST, [](){
    // Envía el JSON por el puerto serie a la Arduino Uno
    nodemcu_softSerial.println("Laser On/Off");
    server.send(200, "text/plain", "OK");
  });

  server.on("/config/autoplay", HTTP_POST, [](){
    nodemcu_softSerial.println("Autoplay");
    server.send(200, "text/plain", "OK");
  });

  server.on("/config/autoplay/speedup", HTTP_POST, [](){
    nodemcu_softSerial.println("Speed Up");
    server.send(200, "text/plain", "OK");
  });

  server.on("/config/autoplay/speeddown", HTTP_POST, [](){
    nodemcu_softSerial.println("Speed Down");
    server.send(200, "text/plain", "OK");
  });

  server.on("/config/area/increase", HTTP_POST, [](){
    nodemcu_softSerial.println("Area +");
    server.send(200, "text/plain", "OK");
  });

  server.on("/config/area/decrease", HTTP_POST, [](){
    nodemcu_softSerial.println("Area -");
    server.send(200, "text/plain", "OK");
  });

  server.on("/config/corners", HTTP_POST, [](){
    nodemcu_softSerial.println("Corners");
    server.send(200, "text/plain", "OK");
  });

  server.on("/move/random", HTTP_POST, [](){
    nodemcu_softSerial.println("Random Position");
    server.send(200, "text/plain", "OK");
  });

  server.on("/move/up", HTTP_POST, [](){
    nodemcu_softSerial.println("Up");
    server.send(200, "text/plain", "OK");
  });

  server.on("/move/down", HTTP_POST, [](){
    nodemcu_softSerial.println("Down");
    server.send(200, "text/plain", "OK");
  });

  server.on("/move/left", HTTP_POST, [](){
    nodemcu_softSerial.println("Left");
    server.send(200, "text/plain", "OK");
  });

  server.on("/move/right", HTTP_POST, [](){
    nodemcu_softSerial.println("Right");
    server.send(200, "text/plain", "OK");
  });

  server.enableCORS(true);
  server.begin();
}

void loop() {
  server.handleClient();
}
