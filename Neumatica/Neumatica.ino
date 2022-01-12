///Codigo 1
/*
int pin2= 9;   //Entrada 2 del L293D
int pin7=10;  //Entrada 7 del L293D
int pote=A0;   //Potenciómetro
 
int valorpote;     //Variable que recoge el valor del potenciómetro
int pwm1;          //Variable del PWM 1
int pwm2;          //Variable del PWM 2
 
void setup()
{
  Serial.begin(9600);
  pinMode(pin2,OUTPUT);
  pinMode(pin7, OUTPUT);
}
 
void loop()
{
  Serial.println(valorpote); //Muestra la lectura que se hace en la entrada analoga
  delay(1000);
  valorpote=analogRead(pote); //Almacenamos el valor del potenciómetro en la variable
 
  //Como la entrada analógica del Arduino es de 10 bits, el rango va de 0 a 1023.
  //En cambio, la salidas del Arduio son de 8 bits, quiere decir, rango entre 0 a 255.
  //Por esta razón tenemos que mapear el número de un rango a otro usando este código.
 // pwm1 = map(valorpote, 0, 1023, 0, 255);
 
if (valorpote > 200){  // Esto puede ser un sensor cuando la señal que desemos cubra un rango gira la rueda

	 analogWrite(pin2,120);
}
else {
	analogWrite(pin2,0);
}

 
}

*/
//////// Si fuera digital usamos

int PinA = 10; // Pines 10 y 9 del arduino
int PinB = 9;
int POT = 0;

int valorpot;
void setup()
{
	pinMode(PinA, OUTPUT);
	pinMode(PinB,  OUTPUT );
	digitalWrite(PinA, LOW);		
	digitalWrite(PinA,LOW);
}

void loop()
{
	valorpot =  analogRead(POT);
	if(valorpot <504){
		digitalWrite(PinA, HIGH);		
		digitalWrite(PinA,LOW);
	}
	else if (valorpot > 520){
		digitalWrite(PinA, LOW);		
		digitalWrite(PinA,HIGH);
	}
	else{
		digitalWrite(PinA, 	LOW);		
		digitalWrite(PinA,LOW);
	}
}