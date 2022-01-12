/*
  www.diymakers.es
  by A.García
  Mover motores paso a paso con Arduino
  Tutorial en: http://diymakers.es/mover-motores-paso-paso-con-arduino/
*/
 
#include <Stepper.h> //Importamos la librería para controlar motores paso a paso
 
#define STEPS 200 //Ponemos el número de pasos que necesita para dar una vuelta. 200 en nuestro caso
 
// Ponemos nombre al motor, el número de pasos y los pins de control
Stepper stepper(STEPS, 4, 5, 6, 7); //Stepper nombre motor (número de pasos por vuelta, pins de control)
 
void setup()
{
  // Velocidad del motor en RPM
  stepper.setSpeed(20);
}
 
void loop()
{
  //Girar una vuelta entera en un sentido
  stepper.step(200);
  delay(500); //Pequeña pausa
 
  //Girar una vuelta entera en sentido contrario
  stepper.step(-200);
  delay(500); //Pequeña pausa
}