int time = 100;
int Leds[] = {5,6,7};
int cont = 3;
int input;

void setup() {

  Serial.begin(9600);
  for(int pin = 0; pin < cont; pin++){
    pinMode(Leds[pin], OUTPUT);
    
  }

}

void loop() {
  if (Serial.available()>0){
    input = Serial.read();
  }

  if(input == 'A'){
    digitalWrite(Leds[0],HIGH); 
  }
  else if (input == 'B'){
    digitalWrite(Leds[1],HIGH); 
  }
  else if (input == 'C'){
    digitalWrite(Leds[2],HIGH);
  }
  else if(input == 'D'){
    digitalWrite(Leds[2],LOW);
  }


}
