volatile int NumPulsos; //variable para la cantidad de pulsos recibidos
int PinSensor = 2;    //Sensor conectado en el pin 2
float factor_conversion=3.7; //para convertir de frecuencia a caudal
float volumen=0;
long dt=0; //variación de tiempo por cada bucle
long t0=0; //millis() del bucle anterior

int AZUL=10;
int AMARILLO=11;
int ROJO=12;

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

void setup() 
{ 
  
  Serial.begin(9600); 
  pinMode(PinSensor, INPUT); 
  pinMode(AZUL,OUTPUT);
  pinMode(AMARILLO,OUTPUT);
  pinMode(ROJO,OUTPUT);
  attachInterrupt(0,ContarPulsos,RISING);//(Interrupción 0(Pin2),función,Flanco de subida)
  Serial.println ("Envie 'r' para restablecer el volumen a 0 Litros"); 
  t0=millis();


  
} 

void loop ()    
{
  if (Serial.available()) {
    if(Serial.read()=='r')volumen=0;//restablecemos el volumen si recibimos 'r'
  }
  float frecuencia=ObtenerFrecuecia(); //obtenemos la frecuencia de los pulsos en Hz
  float caudal_L_m=frecuencia/factor_conversion; //calculamos el caudal en L/m
  dt=millis()-t0; //calculamos la variación de tiempo
  t0=millis();
  volumen=volumen+(caudal_L_m/60)*(dt/1000); // volumen(L)=caudal(L/s)*tiempo(s)

   //-----Enviamos por el puerto serie---------------
  Serial.print ("Caudal: "); 
  Serial.print (caudal_L_m,3); 
  Serial.print ("L/mintVolumen: "); 
  Serial.print (volumen,3); 
  Serial.println (" L");

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

