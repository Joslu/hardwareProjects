//#1 Conectando a la red WiFi desde NodeMCU

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
 
// Definimos parámetros
#define WIFISID "MiHogar"
#define WIFIPASS "Kamilo2016"
 
// Definimos los parámetros para el IFTTT
#define HOSTIFTTT "maker.ifttt.com"
#define EVENTO "nombre_tu_evento"
#define IFTTTKEY "tu_clave_ifttt"
#define LED 2

ESP8266WiFiMulti WiFiMulti;
 
// Utilizamos la conexión SSL del ESP8266
WiFiClientSecure client;
 
// Variable que permite ejecutar una sola vez la función
bool ejecutado = false;
 
void setup() {
 Serial.begin(115200);
 delay(10);
 pinMode(LED,OUTPUT);
 digitalWrite(LED,HIGH);
 // Conectamos a la red WiFi
 WiFiMulti.addAP(WIFISID, WIFIPASS);
 
 Serial.println();
 Serial.println();
 Serial.print("Eperando a conectar a la WiFi... ");
 
 while (WiFiMulti.run() != WL_CONNECTED) {
 Serial.print(".");
 digitalWrite(LED,HIGH);
 delay(500);
 digitalWrite(LED,LOW);
 delay(500);
 }
 
 Serial.println("");
 Serial.println("WiFi conectada");
 Serial.println("Direccion IP: ");
 Serial.println(WiFi.localIP());
 
 
 delay(500);
 
 //Establecemos la semilla en un pin analogico
 randomSeed(analogRead(A0));
}
 
void loop() {
 
}