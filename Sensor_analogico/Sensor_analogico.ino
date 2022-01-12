#define pin_sensor A0 //Pin del sensor
float adc; //Variable para obtener los valores en el 1 paso
float voltaje; //Variable para obtener el voltaje en el 2 paso
float variable; //Variable final del sensor en el 3 paso
float rel_voltaje_variable = 100.00; //Relación Voltaje/Variable del sensor (en el caso del LM35 es 100)
 
void setup()
{
  Serial.begin(9600);
}
 
void loop()
{
  //Paso 1, conversión ADC de la lectura del pin analógico
  adc = analogRead(pin_sensor);
  Serial.println(adc);
 
  //Paso 2, obtener el voltaje
  voltaje = adc * 5 / 1023;
  Serial.println(voltaje);
 
  //Paso 3, obtener la variable de medida del sensor
  variable = voltaje * rel_voltaje_variable;
  Serial.println(variable);
 
  delay(1000);
}
