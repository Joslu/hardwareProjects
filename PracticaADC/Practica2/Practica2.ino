void setup() {                   
  

pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
pinMode(11, OUTPUT);
pinMode(12, OUTPUT);

Serial.begin(9600); 



}

void loop() {                 
  int sensorValue=analogRead(A3);


  Serial.print("Decimalt = ");
  Serial.print(sensorValue);         
  Serial.print("\t Binaert = ");      
  Serial.println(sensorValue, BIN);
  digitalWrite(13, HIGH);             

  
//if(sensorValue >=0 && sensorValue <=1023) {
  digitalWrite(12, (bool)(sensorValue & 1));
  digitalWrite(11 ,(bool)(sensorValue & 2));
  digitalWrite(10, (bool)(sensorValue & 4));
  digitalWrite(9, (bool)(sensorValue & 8));
  digitalWrite(8, (bool)(sensorValue & 16));
  digitalWrite(7, (bool)(sensorValue & 32));
  digitalWrite(6, (bool)(sensorValue & 64));
  digitalWrite(5, (bool)(sensorValue & 128));
  digitalWrite(4, (bool)(sensorValue & 256));
  digitalWrite(3, (bool)(sensorValue & 512));
  
  

 
delay(500);                       
 
}
