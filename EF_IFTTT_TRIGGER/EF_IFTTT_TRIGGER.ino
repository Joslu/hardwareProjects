#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
 
// Definimos parámetros
#define WIFISID "MiHogar"
#define WIFIPASS "Kamilo2016"
 
// Definimos los parámetros para el IFTTT
#define HOSTIFTTT "maker.ifttt.com"
#define EVENTO "Lab_control"
#define IFTTTKEY "POikm4lflsmBUpxBmYSS9"
 
#define LED 2


const char* resource = "/trigger/Lab_control/with/key/POikm4lflsmBUpxBmYSS9";

// How your resource variable should look like, but with your own API KEY (that API KEY below is just an example):
//const char* resource = "/trigger/bme280_readings/with/key/nAZjOphL3d-ZO4N3k64-1A7gTlNSrxMJdmqy3";

// Maker Webhooks IFTTT
const char* server = "maker.ifttt.com";

ESP8266WiFiMulti WiFiMulti;
 

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
  
  if (!ejecutado)
  {
    // Obtenemos los valores
    int valor1 = (int)random(12, 40);
    int valor2 = (int)random(50, 99);
    int valor3 = (int)random(50, 99);
 
    Serial.println(valor1);
    Serial.println(valor2);
    Serial.println(valor3);
 
    makeIFTTTRequest(valor1, valor2, valor3);
    ejecutado = true;
  }
}
 


void makeIFTTTRequest(int valor1, int valor2, int valor3) {
  Serial.print("Connecting to "); 
  Serial.print(server);
  
  WiFiClient client;
  int retries = 5;
  while(!!!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if(!!!client.connected()) {
    Serial.println("Failed to connect...");
  }
  
  Serial.print("Request resource: "); 
  Serial.println(resource);

 
  String jsonObject = String("{\"value1\":\"") + valor1 + "\",\"value2\":\"" + valor2
                      + "\",\"value3\":\"" + valor3 + "\"}";
                      
 
                      
  client.println(String("POST ") + resource + " HTTP/1.1");
  client.println(String("Host: ") + server); 
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);
        
  int timeout = 5 * 10; // 5 seconds             
  while(!!!client.available() && (timeout-- > 0)){
    delay(100);
  }
  if(!!!client.available()) {
    Serial.println("No response...");
  }
  while(client.available()){
    Serial.write(client.read());
  }
  
  Serial.println("\nclosing connection");
  client.stop(); 
}