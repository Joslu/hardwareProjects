#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
 
// Definimos parámetros
#define WIFISID "MiHogar"
#define WIFIPASS "Kamilo2016"
 
// Definimos los parámetros para el IFTTT
#define HOSTIFTTT "maker.ifttt.com"
#define EVENTO "Lab_control"
#define IFTTTKEY "POikm4lflsmBUpxBmYSS9"

#define sensor A0
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
  pinMode(sensor, INPUT);
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
  
  if (!ejecutado)
  {
    // Obtenemos los valores
    int valor1 = (int)random(12, 40);
    int valor2 = (int)random(50, 99);
    int valor3 = LecturaH();
 
    Serial.println(valor1);
    Serial.println(valor2);
    Serial.println(valor3);
 
    enviar_tweet(valor1, valor2, valor3);
    ejecutado = true;
  }
}
 
void enviar_tweet(int valor1, int valor2, int valor3)
{
  // Cerramos cualquier conexión anterior
  if (client.connected())
  {
    client.stop();
  }
 
  // Esperamos hasta que se hayan enviado todos los datos
  client.flush();

 client.setInsecure();
  // Hacemos la petición mediante SSL
  if (client.connect(HOSTIFTTT, 443)) {
    // Construimos la petición HTTP
    String toSend = "POST /trigger/";
    toSend += EVENTO;
    toSend += "/with/key/";
    toSend += IFTTTKEY;
    toSend += "?value1=";
    toSend += valor1;
    toSend += "&value2=";
    toSend += valor2;
    toSend += "&value3=";
    toSend += valor3;
    toSend += " HTTP/1.1\r\n";
    toSend += "Host: ";
    toSend += HOSTIFTTT;
    toSend += "\r\n";
    toSend += "Connection: close\r\n\r\n";
 
    client.print(toSend);
   
  }
 
  // Esperamos hasta que se hayan enviado todos los datos
  client.flush();
  // Desconectamos del cliente
  client.stop();
}


int LecturaH(){
  int valorHumedad = map(analogRead(sensor), 0, 1023, 100, 0);
  return valorHumedad;
  }
