
#include <Servo.h> 

Servo servo1;
Servo servo2;
const int potpin1 = A1; 
int val1;

void setup() 
{ 

  servo1.attach(9);
  servo2.attach(10);
} 


void loop() 
{ 
  val1= analogRead(potpin1);
  val1=map(val1,0,1023,0,179);
  servo1.write(val1);
  servo2.write(val1);

  delay(100);
}
/////////////////////////////////////////////////////////////////////////////////////