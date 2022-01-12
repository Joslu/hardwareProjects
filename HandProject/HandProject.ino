#include <Servo.h>

Servo PrimerServo;
Servo SegundoServo;
Servo TercerServo;

int angle=0;

void setup()
{
	PrimerServo.attach(10);
	SegundoServo.attach(5);
	TercerServo.attach(4);
	PrimerServo.write(angle)

	
}

void loop()
{
	for (angle = 0; angle < 60; angle += 10){
		PrimerServo.write(angle);
		delay(1000);
	}

	for (angle = 60; angle < 120; angle += 10){
		PrimerServo.write(angle);
		delay(1000);
	}
	
	for (angle = 120;  angle <=180; angle += 10){
		PrimerServo.write(angle);
		delay(1000);

	}
}

