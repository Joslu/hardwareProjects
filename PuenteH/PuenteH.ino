#define EA 11
#define I1 10
#define I2 9
 
void setup()
{
pinMode(EA, OUTPUT);
pinMode(I1, OUTPUT);
pinMode(I2, OUTPUT);
}
 
void loop()
{
//Establecemos la velocidad a 200
analogWrite(EA, 200);
 
//Hacia delante
digitalWrite(I1, HIGH);
digitalWrite(I2, LOW);
 
delay(2000);
 
//Y para atras
digitalWrite(I1, LOW);
digitalWrite(I2, HIGH);
 
delay(2000);
}
