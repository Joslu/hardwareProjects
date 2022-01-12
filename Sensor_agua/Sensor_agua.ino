volatile int NumPulsos; //variable para la cantidad de pulsos recibidos
int PinSensor = 2;    //Sensor conectado en el pin 2
float factor_conversion=7.5; //para convertir de frecuencia a caudal
int AZUL = 10;
int AMARILLO = 11;
int ROJO = 12;

//---Función que se ejecuta en interrupción---------------
void ContarPulsos ()
{ 
  NumPulsos++;  //incrementamos la variable de pulsos
} 

//---Función para obtener frecuencia de los pulsos--------
int ObtenerFrecuencia() 
{
  int frecuencia;
  NumPulsos = 0;   //Ponemos a 0 el número de pulsos
  interrupts();    //Habilitamos las interrupciones
  delay(1000);   //muestra de 1 segundo
  noInterrupts(); //Desabilitamos las interrupciones
  frecuencia=NumPulsos; //Hz(pulsos por segundo)
  return frecuencia;
}

void setup()
{ 
  Serial.begin(9600); 
  pinMode(PinSensor, INPUT); 
  pinMode (AZUL, OUTPUT);
  pinMode(ROJO,OUTPUT);
  attachInterrupt(0,ContarPulsos,RISING); //(Interrupcion 0(Pin2),funcion,Flanco de subida)
  
} 

void loop ()    
{
  float frecuencia=ObtenerFrecuencia(); //obtenemos la Frecuencia de los pulsos en Hz
  float caudal_L_m=frecuencia/factor_conversion; //calculamos el caudal en L/m
  float caudal_L_h=caudal_L_m*60; //calculamos el caudal en L/h

  if (caudal_L_m == 0){
    digitalWrite(AZUL,HIGH);
    digitalWrite(ROJO,LOW);
  }
  else{
    digitalWrite(AZUL,LOW);
    digitalWrite(ROJO,HIGH);
  }
   
  
  //-----Enviamos por el puerto serie---------------
  Serial.print ("FrecuenciaPulsos: "); 
  Serial.print (frecuencia,0); 
  Serial.print ("HztCaudal: "); 
  Serial.print (caudal_L_m,3); 
  Serial.print (" L/m  "); 
   Serial.print (caudal_L_h,3); 
  Serial.println (" L/h"); 
}

void Gasto_alto(float caudal_L_m,int ROJO){
  if (caudal_L_m >= 31){
    digitalWrite(ROJO,HIGH);
  }
  else{
    digitalWrite(ROJO,LOW);
  }
  
}

void Gasto_medio(float caudal_L_m,int AMARILLO){
  if (caudal_L_m >= 31){
    digitalWrite(AMARILLO,HIGH);
  }
  else{
    digitalWrite(AMARILLO,LOW);
  }
  
}

void Gasto_BAJO(float caudal_L_m){
  if (caudal_L_m == 0){
    digitalWrite(AZUL,HIGH);
  }
  else{
    digitalWrite(AZUL,LOW);
  }
  
}

