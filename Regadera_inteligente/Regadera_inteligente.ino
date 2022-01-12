/*Programa regadera inteligente*/
#include <Servo.h>
Servo miServo;
//Variables gasto
volatile int NumPulsos; //variable para la cantidad de pulsos recibidos
float factor_conversion=3.7; //para convertir de frecuencia a caudal
float volumen=0;
long dt=0; //variación de tiempo por cada bucle
long t0=0; //millis() del bucle anterior

//Variables sistema
int hab = 0;
float miliVolts;
float temperaturaC;
int angulo ;
int angopen = 135;
int angclose = 28;
float limitemp = 20;

//Pines
int AZUL=10;
int AMARILLO=11;
int ROJO=12;
int PinSensor = 2;    //Sensor fuljo de agua 
int tempPin = 0;

//Start
int start=1;

void setup() {
  Serial.begin(9600);   
  Inicio();

  pinMode(13, OUTPUT);
  pinMode(PinSensor, INPUT); 
  pinMode(AZUL,OUTPUT);
  pinMode(AMARILLO,OUTPUT);
  pinMode(ROJO,OUTPUT);
  pinMode(start,INPUT);
  attachInterrupt(0,ContarPulsos,RISING);//(Interrupción 0(Pin2),función,Flanco de subida)
  Serial.println ("Envie 'r' para restablecer el volumen a 0 Litros"); 
  t0=millis();


}

void loop() {
  
    Sistema();

  if (Serial.available()) {
    if(Serial.read()=='1'){
  Serial.print("Temperatura:  ");
  Serial.print(temperaturaC);
  Serial.print("  C   ");
  Serial.print("Angulo:  ");
  Serial.print(angulo);
  Serial.println("  grados");
  delay(500);
      
    }
  }

  else if(Serial.read()=='2') {


     //-----Enviamos por el puerto serie---------------
  Serial.print ("Caudal: "); 
  Serial.print (caudal_L_m,3); 
  Serial.print ("L/mintVolumen: "); 
  Serial.print (volumen,3); 
  Serial.println (" L");   
  }



  

}


void gasto_de_agua(){
  
    
  float frecuencia=ObtenerFrecuecia(); //obtenemos la frecuencia de los pulsos en Hz
  float caudal_L_m=frecuencia/factor_conversion; //calculamos el caudal en L/m
  dt=millis()-t0; //calculamos la variación de tiempo
  t0=millis();
  volumen=volumen+(caudal_L_m/60)*(dt/1000); // volumen(L)=caudal(L/s)*tiempo(s)


  if (volumen >=0.001 && volumen < .50 && caudal_L_m !=0){
    digitalWrite(AZUL,HIGH);
    digitalWrite(ROJO,LOW);
    digitalWrite(AMARILLO,LOW);
  }

  else if (volumen >=0.5 && volumen < .80 && caudal_L_m !=0){
    digitalWrite(AZUL,HIGH);
    digitalWrite(ROJO,LOW);
    digitalWrite(AMARILLO,HIGH);
  }
  else if (volumen >= 0.80 && caudal_L_m !=0){
    digitalWrite(AZUL,HIGH);
    digitalWrite(ROJO,HIGH);
    digitalWrite(AMARILLO,HIGH);
  }

   else if  (caudal_L_m ==0 && volumen > 0.80)
  {
     digitalWrite(AZUL,LOW);
    digitalWrite(ROJO,LOW);
    digitalWrite(AMARILLO,LOW);
    volumen =0;
  }
 
  
}




//---Función que se ejecuta en interrupción---------------
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

void Inicio(){
  delay(3000);
  miServo.attach(6);
  miServo.write(angclose);
}

void Sistema(){
  // put your main code here, to run repeatedly:
 temperaturaC = analogRead(tempPin); 
 temperaturaC = (5.0 * temperaturaC * 100.0)/1024.0;
  if ((temperaturaC >= limitemp) && (hab == 0))
  {
    digitalWrite(13, HIGH);
    angulo = angopen;
    miServo.write(angulo);
    delay(1000);
    hab = 1;
  }
  else if ((temperaturaC < limitemp) && (hab == 1))
  {
    digitalWrite(13, LOW);
    angulo = angclose;
    miServo.write(angulo);
    delay(1000);
    hab = 0;
  }
 
}

