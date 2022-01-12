
#include <IRremote.h>

#define TECLA0 0xFF9867
#define TECLA1 0xFFA25D
#define TECLAOK 0xFF38C7

int receptor = 9;
int LED = 11;
IRrecv irrecv(receptor);
decode_results codigo; //OBJETO CODIGO DE CLASE decode_result, oriundo de IRremote.h


//Motores Conexión
const int pinPWMA = 5;
const int pinAIN2 = 3;
const int pinAIN1 = 2;
const int pinBIN1 = 7;
const int pinBIN2 = 8;
const int pinPWMB = 6;
const int pinSTBY = 4;
 
const int waitTime = 1000;   //espera entre fases
const int speed = 200;      //velocidad de giro
 
const int pinMotorA[3] = { pinPWMA, pinAIN2, pinAIN1 };
const int pinMotorB[3] = { pinPWMB, pinBIN1, pinBIN2 };
 
enum moveDirection {
   forward,
   backward
};
 
enum turnDirection {
   clockwise,
   counterClockwise
}; 
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // INICIA LA RECEPCIÓN
  pinMode(LED, OUTPUT);
  digitalWrite(LED,HIGH);
}
 
void loop()
{
 if (irrecv.decode(&codigo))
 {
Serial.println(codigo.value, HEX);

      if (codigo.value==0xFFA25D)//Telca 1
      {
         digitalWrite(LED,HIGH);
      }

      if (codigo.value==0xFF9867)//Tecla 0
      {
         digitalWrite(LED,LOW);
         
      
      }

      if (codigo.value==0xFF38C7)//Tecla ok
      {
      
         digitalWrite(LED,HIGH);
         delay(500);
         digitalWrite(LED,LOW);
         delay(500);
         digitalWrite(LED,HIGH);
         delay(500);
         digitalWrite(LED,LOW);
         delay(500);
      }
    
    
delay(500);
irrecv.resume();

 }
}

 
//Funciones que controlan el vehiculo
void move(int direction, int speed)
{
   if (direction == forward)
   {
      moveMotorForward(pinMotorA, speed);
      moveMotorForward(pinMotorB, speed);
   }
   else
   {
      moveMotorBackward(pinMotorA, speed);
      moveMotorBackward(pinMotorB, speed);
   }
}
 
void turn(int direction, int speed)
{
   if (direction == forward)
   {
      moveMotorForward(pinMotorA, speed);
      moveMotorBackward(pinMotorB, speed);
   }
   else
   {
      moveMotorBackward(pinMotorA, speed);
      moveMotorForward(pinMotorB, speed);
   }
}
 
void fullStop()
{
   disableMotors();
   stopMotor(pinMotorA);
   stopMotor(pinMotorB);
}
 
//Funciones que controlan los motores
void moveMotorForward(const int pinMotor[3], int speed)
{
   digitalWrite(pinMotor[1], HIGH);
   digitalWrite(pinMotor[2], LOW);
 
   analogWrite(pinMotor[0], speed);
}
 
void moveMotorBackward(const int pinMotor[3], int speed)
{
   digitalWrite(pinMotor[1], LOW);
   digitalWrite(pinMotor[2], HIGH);
 
   analogWrite(pinMotor[0], speed);
}
 
void stopMotor(const int pinMotor[3])
{
   digitalWrite(pinMotor[1], LOW);
   digitalWrite(pinMotor[2], LOW);
 
   analogWrite(pinMotor[0], 0);
}
 
void enableMotors()
{
   digitalWrite(pinSTBY, HIGH);
}
 
void disableMotors()
{
   digitalWrite(pinSTBY, LOW);
}

