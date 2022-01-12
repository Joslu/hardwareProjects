

void setup() {
  pinMode(10,OUTPUT); //B
  pinMode(11,OUTPUT); //A
  digitalWrite(10,HIGH);// B+
  digitalWrite(11,LOW); //A-
}

void loop() {
  digitalWrite(10,HIGH); //B+
  delay(2000);
  digitalWrite(10,LOW);
  delay(2000);
  
  digitalWrite(11,LOW); //A-
  delay(2000);
  digitalWrite(11,HIGH); //A+
  delay(2000);
  digitalWrite(11,LOW);
  delay(2000);

  
  digitalWrite(10,LOW); //B-
  delay(3000);
}
