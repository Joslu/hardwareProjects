#include <Servo.h>
///////Conexiones
//La parte más gruesa del sensor flex se conecta a una resistencia que va a 5v.
//El lado delgado se conecta directamente a GND
//El servo se conecta de forma normal, usamos un potenciometro para mover motor tambien 


Servo Servo1;
Servo Servo2;
Servo Servo3;

int angle = 90;
int flex[20];
int flexsum=0;
int SensorFlex = A0;
int Pot1 = A1;
int val1;
void setup()
{
	Servo1.attach(10);
	Servo2.attach(9);
	Serial.begin(9600);
}

void loop()
{
	for (int x = 0; x < 20; x++){
		flex[x] = analogRead(SensorFlex);
		flexsum = flexsum + analogRead(SensorFlex);
		delayMicroseconds(14);
	}
	flexsum = flexsum/20;

  Serial.print("sensor: ");
  Serial.print(flexsum);
  Serial.print("  servo: ");
  Serial.println(angle);


  	//Potenciometro 1
  	val1 = analogRead(Pot1);
  	val1=map(val1,0,1023,0,179);
  	Servo2.write(val1);

  	///Sensor
	angle = map (flexsum, 861 , 1076, 0, 180);
	Servo1.write(angle);
	delay(15);
}



