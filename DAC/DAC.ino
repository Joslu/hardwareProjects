void setup() 
{

  for (int i = 0; i < 10; i++){
      pinMode(i,OUTPUT);
  }

}

void loop() {
  PORTD = 1023;

}
