#define sensor A0
 
void setup(){
	pinMode(sensor, INPUT);
	Serial.begin(9600);
}
 
void loop(){
	
	//Se hace la lectura analoga del pin A0 (sensor) y se pasa por la funcion
	//map() para ajustar los valores leidos a los porcentajes que queremos utilizar		
	int valorHumedad = map(analogRead(sensor), 0, 1023, 100, 0);
	
	Serial.print("Humedad: ");
	Serial.print(valorHumedad);
	Serial.println("%");
 
	delay(100);
}