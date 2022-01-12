#include "Perceptron.h"

perceptron MyPerceptron(3); //Tres entradas más el bias

#define N 5 //Número de frutas
const int EchoPin = 11;
const int TriggerPin = 12;

#define CLlimones 4
#define CLTomates 5

#define S0 43 //Naranja
#define S1 45 //Morado
#define S2 40 //Azul
#define S3 42 //Café
#define sensorOut 44 //Amarillo

/*+++++++++++++++++++++++*/
#define S_HOME 0
#define S_TRAINNING 1
#define S_TEST 2

uint8_t state = S_HOME ; // Estado Actual, lo colocamos en home 

#define BTN_HOME 0
#define BTN_TRAINNING 1
#define BTN_TEST 2
#define BTN_NEW 3



uint8_t button[6] = {
  24,
  26,
  28,
  30
 };

uint8_t led[4] = {
  34,
  36,
  38,
  40
   
  };

uint8_t button_estate[6];

uint8_t flancoSubida(int btn) {
  uint8_t valor_nuevo = digitalRead(button[btn]);
  uint8_t result = button_estate[btn]!=valor_nuevo && valor_nuevo == 1;
  button_estate[btn] = valor_nuevo;
  return result;
}

int Data[N][3];
float Pesos[] = {0,0,0,0,0};

int X[3] = { 0 };

void setup() {
  Serial.begin(9600);
  Serial.println("Inicio");
  Serial.println();

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  pinMode(CLlimones, OUTPUT);
  pinMode(CLTomates,OUTPUT);

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

  for(int i = 0; i < 4; i++){
      pinMode(led[i],OUTPUT);
      digitalWrite(led[i],LOW);
    }

  


  button_estate[0] = HIGH; //Resistencias como PULLUP
  button_estate[1] = HIGH; 
  button_estate[2] = HIGH; 
  button_estate[3] = HIGH; 

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
                  Serial.print(Data[i][j]);
              }
              Serial.println();
           }
          
          Serial.println();
          delay(3000);
            state = S_HOME;
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
      
       if (flancoSubida(BTN_HOME)){
           state = S_HOME;
            break;
        }

       if (flancoSubida(BTN_NEW)){
          state = S_TRAINNING;
          getData(); //Aquirir datos
          MyPerceptron.randomize();

       
       
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

       if (flancoSubida(BTN_HOME)){
           state = S_HOME;
            break;
          
        }
         if (flancoSubida(BTN_NEW)){

           for (int i = 0; i <N; i++) {
              for (int j = 0; j < 3; j++) {
                  Serial.print("  ");
                  Serial.print(Data[i][j]);
              }
              Serial.println();
           }
          
          Serial.println();

            MyPerceptron.inputs[0] = ping(TriggerPin,EchoPin);;
            MyPerceptron.inputs[1] = color();
            if (MyPerceptron.inputs[0] <= 8){
                MyPerceptron.inputs[2] = 1;}
                else{
                MyPerceptron.inputs[2] = -1;
                }
      
          float guess = MyPerceptron.feedForward();

      

        if (MyPerceptron.inputs[2] == 1) {
            Serial.println("Manzana");
            digitalWrite(7, HIGH);
            digitalWrite(6, LOW);
            }
        else {
            Serial.println("Limon");
            digitalWrite(7, LOW);
            digitalWrite(6, HIGH);
            }
   
          state = S_TEST;
          break;
        } 

        
          
    
    break;
      
    
  }
  

}




uint8_t getData(){

  for(int Nobjeto = 0; Nobjeto < N ; Nobjeto++){
     
     Data[Nobjeto][0] = ping(TriggerPin,EchoPin);
     Data[Nobjeto][1] = color();
     if (Data[Nobjeto][0] <= 8){
      Data[Nobjeto][2] = 1;}
     else{
      Data[Nobjeto][2] = -1;
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

uint8_t color()
{
  uint8_t redColor = 0;
  uint8_t greenColor = 0;
  uint8_t redFrequency = 0;
  uint8_t greenFrequency = 0;
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  redFrequency = pulseIn(sensorOut, LOW);
  redColor = map(redFrequency, 47, 248, 255,0);

   // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  greenFrequency = pulseIn(sensorOut, LOW);
  greenColor = map(greenFrequency, 124, 424, 255, 0);

  if(redColor > greenColor ){
      return redColor;
  }

   if(greenColor > redColor){
    return greenColor;
  }
  }






