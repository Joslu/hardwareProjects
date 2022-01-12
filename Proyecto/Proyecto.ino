//Regadera inteligente

#include <Servo.h>
Servo miServo;
int angulo ;
int angopen = 135;
int angclose = 28;
float limitemp = 20;
int hab=0;

//Variables Globales
float temperaturaC;
volatile int NumPulsos;
float volumen=0;
long dt=0; //variación de tiempo por cada bucle
long t0=0; //millis() del bucle anterior

//Pines
int sensorAgua = 2;
int Azul = 10;
int Amarillo = 11;
int Rojo = 12;
int sensorTemp = A0;
int Aviso =13;

void setup() {
  Serial.begin(9600); 
  pinMode(sensorAgua, INPUT); 
  pinMode(Azul,OUTPUT);
  pinMode(Amarillo,OUTPUT);
  pinMode(Rojo,OUTPUT);
  pinMode(Aviso,OUTPUT);
  attachInterrupt(0,ContarPulsos,RISING);//(Interrupción 0(Pin2),función,Flanco de subida)
  t0=millis();
  Iniciar_servo();

}

void loop ()    
{
 
  float factor_conversion=3.7;
  float frecuencia=ObtenerFrecuecia(); //obtenemos la frecuencia de los pulsos en Hz
  float caudal_L_m=frecuencia/factor_conversion; //calculamos el caudal en L/m
  dt=millis()-t0; //calculamos la variación de tiempo
  t0=millis();
  volumen=volumen+(caudal_L_m/60)*(dt/1000); // volumen(L)=caudal(L/s)*tiempo(s)
   int hab = 0;
 temperaturaC = analogRead(sensorTemp); 
 temperaturaC = (5.0 * temperaturaC * 100.0)/1024.0;


   if ((temperaturaC >= limitemp) && (hab == 0)){
    digitalWrite(13, HIGH);
    angulo = angopen;
    miServo.write(angulo);
    delay(1000);
    hab = 1;
    
     if (volumen >=0.001 && volumen < .50 && caudal_L_m !=0 && temperaturaC >= (limitemp) && (hab == 0) ){
    digitalWrite(Azul,HIGH);
    digitalWrite(Rojo,LOW);
    digitalWrite(Amarillo,LOW);
    if ((temperaturaC < limitemp) && (hab == 1))
  {
    digitalWrite(13, LOW);
    angulo = angclose;
    miServo.write(angulo);
    delay(1000);
    hab = 0;
    digitalWrite(Azul,LOW);
    digitalWrite(Rojo,LOW);
    digitalWrite(Amarillo,LOW);
    volumen =0;
  }
  }

  else if (volumen >=0.5 && volumen < .80 && caudal_L_m !=0 && temperaturaC >= (limitemp) && (hab == 0)){
    digitalWrite(Azul,HIGH);
    digitalWrite(Rojo,LOW);
    digitalWrite(Amarillo,HIGH);
    if ((temperaturaC < limitemp) && (hab == 1))
  {
    digitalWrite(13, LOW);
    angulo = angclose;
    miServo.write(angulo);
    delay(1000);
    hab = 0;
    digitalWrite(Azul,LOW);
    digitalWrite(Rojo,LOW);
    digitalWrite(Amarillo,LOW);
    volumen =0;
  }
  }
  else if (volumen >= 0.80 && caudal_L_m !=0 && temperaturaC >= (limitemp) && (hab == 0)){
      digitalWrite(Azul,HIGH);
    digitalWrite(Rojo,HIGH);
    digitalWrite(Amarillo,HIGH);
    if ((temperaturaC < limitemp) && (hab == 1))
  {
    digitalWrite(13, LOW);
    angulo = angclose;
    miServo.write(angulo);
    delay(1000);
    hab = 0;
    digitalWrite(Azul,LOW);
    digitalWrite(Rojo,LOW);
    digitalWrite(Amarillo,LOW);
    volumen =0;
  }
  }

   else if  (caudal_L_m ==0 && volumen > 0.80 && temperaturaC >= (limitemp) && (hab == 0))
  {
     digitalWrite(Azul,LOW);
    digitalWrite(Rojo,LOW);
    digitalWrite(Amarillo,LOW);
    volumen =0;
    if ((temperaturaC < limitemp) && (hab == 1))
  {
    digitalWrite(13, LOW);
    angulo = angclose;
    miServo.write(angulo);
    delay(1000);
    hab = 0;
    digitalWrite(Azul,LOW);
    digitalWrite(Rojo,LOW);
    digitalWrite(Amarillo,LOW);
    volumen =0;
  }
  }
   }

  else if ((temperaturaC < limitemp) && (hab == 1))
  {
    digitalWrite(13, LOW);
    angulo = angclose;
    miServo.write(angulo);
    delay(1000);
    hab = 0;
    digitalWrite(Azul,LOW);
    digitalWrite(Rojo,LOW);
    digitalWrite(Amarillo,LOW);
    volumen =0;
  }
  Serial.print("Temperatura:  ");
  Serial.print(temperaturaC);
  Serial.print("  C   ");
   Serial.print (volumen,3); 
  Serial.println (" L");
  }
 






////////////////////// Código que obtiene el gasto de agua//

void ContarPulsos ()  
{ 
  NumPulsos++;  //incrementamos la variable de pulsos
} 

//---Función para obtener frecuencia de los pulsos--------
int ObtenerFrecuecia() 
{
  int frecuencia;
  NumPulsos = 0;   //Ponemos a 0 el número de pulsos
  interrupts();    //Habilitamos las interrupciones
  delay(1000);   //muestra de 1 segundo
  noInterrupts(); //Deshabilitamos  las interrupciones
  frecuencia=NumPulsos; //Hz(pulsos por segundo)
  return frecuencia;
}

///////////////código sistema cierra llave


void Iniciar_servo(){
  delay(3000);
  miServo.attach(6);
  miServo.write(angclose);
}

