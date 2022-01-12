#include <Servo.h>
 
// Declaramos la variable para controlar el servo
Servo servoMotor;
int pot = A0;
int val; 

void setup() {
  // Iniciamos el monitor serie para mostrar el resultado
  Serial.begin(9600);
 
  // Iniciamos el servo para que empiece a trabajar con el pin 9
  servoMotor.attach(11);
 
  // Inicializamos al ángulo 0 el servomotor
  servoMotor.write(20);
}
 
void loop() {


  val = analogRead(pot);
  val = map(val,0,1023,0,180);

  servoMotor.write(val);
  delay(15);
}

  /*
  // Vamos a tener dos bucles uno para mover en sentido positivo y otro en sentido negativo
  // Para el sentido positivo
  for (int i = 0; i <= 180; i++)
  {
    // Desplazamos al ángulo correspondiente
    servoMotor.write(i);
    Serial.println(i);
    // Hacemos una pausa de 25ms
    delay(25);
  }
 
  // Para el sentido negativo
  for (int i = 180; i > 0; i--)
  {
    // Desplazamos al ángulo correspondiente
    servoMotor.write(i);
    // Hacemos una pausa de 25ms
    delay(25);
  }*/


