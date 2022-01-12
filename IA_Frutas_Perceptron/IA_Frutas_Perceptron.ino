
#include <math.h>
#include <time.h>

#define LR   0.01
#define EXAMPLES 8



#define N 8 //Número de frutas
const int EchoPin = 10;
const int TriggerPin = 9;

char Color;
#define S0 43 //Naranja
#define S1 45 //Morado
#define S2 40 //Azul
#define S3 42 //Café
#define sensorOut 44 //Amarillo

/*+++++++++++++++++++++++*/
#define S_HOME 0
#define S_TRAINNING 1
#define S_TEST 2
#define S_CALIBRATION 3

uint8_t state = S_HOME ; // Estado Actual, lo colocamos en home 

#define BTN_HOME 0
#define BTN_TRAINNING 1
#define BTN_TEST 2
#define BTN_NEW 3
#define BTN_CALIBRATION 4


uint8_t button[5] = {
  24,
  26,
  28,
  30,
  31
 };

uint8_t led[6] = {
  34,
  36,
  38,
  52,
  6,
  7,
   
  };

uint8_t button_estate[6];

uint8_t flancoSubida(int btn) {
  uint8_t valor_nuevo = digitalRead(button[btn]);
  uint8_t result = button_estate[btn]!=valor_nuevo && valor_nuevo == 1;
  button_estate[btn] = valor_nuevo;
  return result;
}

int Data[N][2];
int Data2[N][2];
int DataX[N], DataY[N], DataOUT[N];

float weights[3], localError, auxW[3],globalError;
int patternCount, i, p, iteration, output;


int color1 = 0;
int distancia = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Inicio");
  Serial.println();

  
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);

 

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  
  pinMode(button[BTN_HOME],INPUT_PULLUP);
  pinMode(button[BTN_TEST],INPUT_PULLUP);
  pinMode(button[BTN_TRAINNING],INPUT_PULLUP);
  pinMode(button[BTN_NEW],INPUT_PULLUP);
  pinMode(button[BTN_CALIBRATION],INPUT_PULLUP);

  for(int i = 0; i < 7; i++){
      pinMode(led[i],OUTPUT);
      digitalWrite(led[i],LOW);
    }

  


  button_estate[0] = HIGH; //Resistencias como PULLUP
  button_estate[1] = HIGH; 
  button_estate[2] = HIGH; 
  button_estate[3] = HIGH; 
  button_estate[4] = HIGH; 

}

void loop() {

  switch(state){
    case S_HOME:/*Inicio Home*/
    Serial.println("STATE Home");
    delay(500);

    digitalWrite(led[0],HIGH);
    digitalWrite(led[1],LOW);
    digitalWrite(led[2],LOW);
     digitalWrite(led[3],LOW);
     digitalWrite(led[4],LOW);
     digitalWrite(led[5],LOW);

    
      if (flancoSubida(BTN_TRAINNING)){
          state = S_TRAINNING;
        
          break;
            
        }

       if (flancoSubida(BTN_TEST)){
           state = S_TEST;
            break;
          
        }

        if (flancoSubida(BTN_NEW)){

            for (int i = 0; i <N; i++) {
              for (int j = 0; j < 2; j++) {
                  Serial.print("  ");
                  Serial.print(Data2[i][j]);
              }
              Serial.println();
           }
          
          Serial.println();
          delay(3000);
            
            state = S_HOME;
            break;
          }

         if(flancoSubida(BTN_CALIBRATION)){
          
            state = S_CALIBRATION;
            break;
          }
        
      
        break; /*Fin Home*/
    
    case S_TRAINNING: /*Inicio Trainning*/

      
      Serial.println("STATE Trainning");
      delay(500);

      
      digitalWrite(led[0],LOW);
      digitalWrite(led[1],HIGH);
      digitalWrite(led[2],LOW);
      digitalWrite(led[3],LOW);
      digitalWrite(led[4],LOW);
     digitalWrite(led[5],LOW);
     
      
       if (flancoSubida(BTN_HOME)){
           state = S_HOME;
            break;
        }

       if (flancoSubida(BTN_NEW)){

        getData();
        
        patternCount = EXAMPLES;
        weights[0] = randomFloat();
        weights[1] = randomFloat();
        weights[2] = randomFloat();
        
        iteration = 0;
         do{
            iteration ++;
            globalError = 0;
            for (p = 0; p < N; p++){

              output = calculateOutput(weights,DataX[p],DataY[p]);
              localError = DataOUT[p] - output;
              weights[0] += LR * localError * DataX[p];
              weights[1] += LR * localError * DataY[p];
              weights[2] += LR * localError;

              auxW[0] =  weights[0];
              auxW[1] =  weights[1];
              auxW[2] =  weights[2];

            globalError += (localError*localError);
            }
          
          Serial.println("Iteración: ");
          Serial.print(iteration);
          Serial.print(" ");
          Serial.print(sqrt(globalError/patternCount));
          Serial.println();
          delay(5000);
          
          }while (globalError != 0 && iteration<=10);
         
                  
          state = S_TRAINNING;
         

       
       
          break;
        } 
    
    break;

    case S_TEST:
      
      Serial.println("STATE Test");
      delay(500);

      digitalWrite(led[0],LOW);
      digitalWrite(led[1],LOW);
      digitalWrite(led[2],HIGH);
      digitalWrite(led[3],LOW);
      digitalWrite(led[4],LOW);
     digitalWrite(led[5],LOW);
     
       if (flancoSubida(BTN_HOME)){
           state = S_HOME;
            break;
          
        }
         if (flancoSubida(BTN_NEW)){
          Serial.println(" Pesos");
          for(int i = 0; i<3;i++){
            Serial.print(auxW[i]);
            Serial.print(" ");    
            }
          delay(2000);
          int test;
          test = calculateOutput(auxW,ping(TriggerPin,EchoPin),color());
          if (test == 1){
            Serial.println("Manzana");
            digitalWrite(7, HIGH);
            digitalWrite(6, LOW);
            }
          else{
            Serial.println("Jitomate");
            digitalWrite(7, LOW);
            digitalWrite(6, HIGH);
            }
          
           
   
          state = S_TEST;
          break;
        } 

        
          
    
    break;
  
    case S_CALIBRATION:
      
      Serial.println("STATE Calibration");
      delay(500);

      digitalWrite(led[0],LOW);
      digitalWrite(led[1],LOW);
      digitalWrite(led[2],LOW);
      digitalWrite(led[3],HIGH);
      digitalWrite(led[4],LOW);
     digitalWrite(led[5],LOW);
        
    if (flancoSubida(BTN_HOME)){
           state = S_HOME;
            break;
          
        }

    if(flancoSubida(BTN_TRAINNING)){
      Serial.println("PRUEBA SENSOR DISTANCIA");
      Serial.println();
      delay(500);

       while(1){
      int cm = ping(TriggerPin, EchoPin);
      Serial.print("Distancia: ");
      Serial.println(cm);
      delay(1000);
  
      if (flancoSubida(BTN_CALIBRATION)){
    
            state = S_CALIBRATION;
             break;
      }
      
       }
      break;
      }

   if (flancoSubida(BTN_TEST)){
       Serial.println("PRUEBA SENSOR COLOR");
      Serial.println();
      delay(500);

      while(1){
          Serial.println();
          colorP();
          
  
           if (flancoSubida(BTN_CALIBRATION)){
    
            state = S_CALIBRATION;
             break;
          } 
        
      }
      state = S_CALIBRATION;
      break;
    }
  }
  

}




uint8_t getData(){


  for(int Nobjeto = 0; Nobjeto < N ; Nobjeto++){
     delay(5000);
     Data2[Nobjeto][0] = ping(TriggerPin,EchoPin);
     Data2[Nobjeto][1] =  colorP();
     
     Data[Nobjeto][0] = ping(TriggerPin,EchoPin);
     Data[Nobjeto][1] =colorP();
     DataX[Nobjeto] = Data[Nobjeto][0];
     DataY[Nobjeto] = Data[Nobjeto][1];
     
     if ((Data[Nobjeto][0] <= 8)&&((Data[Nobjeto][1]>=30)&&(Data[Nobjeto][1]<=60))){
      Data[Nobjeto][2] = 1;
      DataOUT[Nobjeto] = Data[Nobjeto][2];}
     else{
      Data[Nobjeto][2] = -1;
      DataOUT[Nobjeto] = Data[Nobjeto][2];
      }

     
     Serial.println("Tenemos: ");
     Serial.print(Data[Nobjeto][0]);
     Serial.print(" ");
     Serial.print(Data[Nobjeto][1]);
     Serial.print(" ");
     Serial.print(Data[Nobjeto][2]);
     Serial.println(); 

    
     digitalWrite(led[3],HIGH);
     delay(5000);
     digitalWrite(led[3],LOW);
    
    }
     
     Serial.print("Vector X: ");
       for(int j = 0; j < N ; j++){
      
         Serial.print(DataX[j]);
         Serial.print(" ");
       }
     delay(2000);
    Serial.println();

    Serial.print("Vector Y: ");
     for(int j = 0; j < N ; j++){
        
         Serial.print(DataY[j]);
         Serial.print(" ");
       }
    delay(2000);
    Serial.println();


    Serial.print("Vector OUT: ");
     for(int j = 0; j < N ; j++){
             
             Serial.print(DataOUT[j]);
             Serial.print(" ");
           }
        delay(2000);
        Serial.println();

    
  }



int ping(int TriggerPin, int EchoPin) {
   long duration, distanceCm;
   
   digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(4);
   digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(TriggerPin, LOW);
   
   duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
   
   distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
   return distanceCm;
}



uint8_t colorP(){

    int redFrequency = 0;
    int greenFrequency = 0;
    int blueFrequency = 0;


    int redColor = 0;
    int greenColor = 0;
    int blueColor = 0;
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  
  redFrequency = pulseIn(sensorOut, LOW); 
  redColor = map(redFrequency, 47, 248, 255,0);
  
  Serial.print("R = ");
  Serial.print(redColor);
  delay(500);
  

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  

  greenFrequency = pulseIn(sensorOut, LOW);
  
  greenColor = map(greenFrequency, 124, 424, 255, 0);
 
  Serial.print(" G = ");
  Serial.print(greenColor);
  delay(500);
 
  
   digitalWrite(S2,LOW);
   digitalWrite(S3,HIGH);
  
   blueFrequency = pulseIn(sensorOut, LOW);
  
   blueColor = map(blueFrequency, 74, 196, 255, 0);

 
  Serial.print(" B = ");
  Serial.print(blueColor);
  delay(500);

  if(redColor > greenColor && redColor > blueColor){
      Serial.println(" - RED detected!");
      return redColor;
  }
  if(greenColor > redColor && greenColor > blueColor){
    Serial.println(" - GREEN detected!");
    return greenColor;
  }
  if(blueColor > redColor && blueColor > greenColor){
    Serial.println(" - BLUE detected!");
  }

  
  
  }


uint8_t color(){

    int redFrequency = 0;
    int greenFrequency = 0;
    int blueFrequency = 0;


    int redColor = 0;
    int greenColor = 0;
    int blueColor = 0;
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  
  redFrequency = pulseIn(sensorOut, LOW); 
  redColor = map(redFrequency, 47, 248, 255,0);


  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  

  greenFrequency = pulseIn(sensorOut, LOW);
  
  greenColor = map(greenFrequency, 124, 424, 255, 0);
 
  
   digitalWrite(S2,LOW);
   digitalWrite(S3,HIGH);
  
   blueFrequency = pulseIn(sensorOut, LOW);
  
   blueColor = map(blueFrequency, 74, 196, 255, 0);



  if(redColor > greenColor && redColor > blueColor){
    
      return redColor;
  }
  if(greenColor > redColor && greenColor > blueColor){
    return greenColor;
  }
  if(blueColor > redColor && blueColor > greenColor){

  }

  
  
  }

float randomFloat()
{
    return (float)rand() / (float)RAND_MAX;
}

int calculateOutput(float weights[], float x, float y)
{
    float sum = x * weights[0] + y * weights[1] + weights[2];
    return (sum >= 0) ? 1 : -1;
}

