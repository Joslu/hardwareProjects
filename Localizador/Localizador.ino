#include "MPU6050.h"
#include <Servo.h>
#include <Math.h>

Servo servoMotor;


long duration;
const int trigPin = 10;
const int echoPin = 11;
float distance;
float distancex;


void setup()
{
	servoMotor.attach(9);
	pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  	pinMode(echoPin, INPUT); // Sets the echoPin as an Input
	Serial.begin(9600);

}

void loop()
{
	 for (int i = 20; i <= 120; i++)
  {
    // Desplazamos al ángulo correspondiente
    servoMotor.write(i);
    distance = GetDistance();
    distancex = distance * (cos(i)*55);

    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
    delay(25);
  }
  // Para el sentido negativo
  for (int i = 120; i > 20; i--)
  {
    // Desplazamos al ángulo correspondiente
    servoMotor.write(i);
    distance = GetDistance();
    distancex = distance * (cos(i)*55);
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
    delay(25);
  }
}

float GetDistance()
{
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;

}
