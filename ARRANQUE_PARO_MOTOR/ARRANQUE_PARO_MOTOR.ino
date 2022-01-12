//Programa para poder re<lizar el sistema de arranque, paro y cambio de giro de un
//motor eléctrico DC. Implementado con una maáquina de estados 

#define S_PARO 0
#define S_ARRANQUE 1
#define S_ANTICLOCKWISE 2

uint8_t state = S_PARO; //Estado actual lo colocamos en paro

#define BTN_PARO 0
#define BTN_ARRANQUE 1
#define BTN_ANTICLOCKWISE 2

#define ENA 11
#define IN1 10
#define IN2 9
#define POT A0

int PotValue;
int PWMOutput;

uint8_t button[3] = {
  3,
  4,
  5 
};

uint8_t button_state[3];

uint8_t leds[4]{
  12,
  13,
  7,
  6
 };

uint8_t flancoSubida(int btn) {
    uint8_t valor_nuevo = digitalRead(button[btn]);
    uint8_t result = button_state[btn]!=valor_nuevo && valor_nuevo == 1;
    button_state[btn] = valor_nuevo;
    return result;
}


void ClockWise(){

  digitalWrite(leds[2],HIGH);
  digitalWrite(leds[3],LOW);
  PotValue = analogRead(POT);
  PWMOutput = map(PotValue,0,1023,0,255);
  analogWrite(ENA,PWMOutput);
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  
  };

void AClockWise(){
  
  digitalWrite(leds[2],LOW);
  digitalWrite(leds[3],HIGH);
  
  PotValue = analogRead(POT);
  PWMOutput = map(PotValue,0,1023,0,255);
  analogWrite(ENA,PWMOutput);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  
  };

void Stop(){

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA,0);
  };


void setup() {
  state = S_PARO;
  Serial.begin(9600);
  Serial.println("Inicio");
  Serial.println();

  pinMode(button[BTN_PARO],INPUT_PULLUP);
  pinMode(button[BTN_ARRANQUE],INPUT_PULLUP);
  pinMode(button[BTN_ANTICLOCKWISE],INPUT_PULLUP);

  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);

  
  button_state[0] = HIGH;
  button_state[1] = HIGH;
  button_state[2] = HIGH;
  
  for(int i = 0; i < 4; i++){
      pinMode(leds[i],OUTPUT);
      digitalWrite(leds [i],LOW);
    }


}

void loop() {
  
  switch(state){

    case S_PARO:

    Serial.println("PARO");
    delay(500);
    
    digitalWrite(leds[0],HIGH);
    digitalWrite(leds[1],LOW);
    digitalWrite(leds[2],LOW);
    digitalWrite(leds[3],LOW);

    Stop();

       if (flancoSubida(BTN_PARO)){
           state = S_PARO;
            break;
          
        }

        if (flancoSubida(BTN_ARRANQUE)){
           state = S_ARRANQUE;
            break;
          
        }

        

        
    break;

    case S_ARRANQUE:
    
    Serial.println("ARRANQUE");
    delay(500);
    
    digitalWrite(leds[0],LOW);
    digitalWrite(leds[1],HIGH);

    ClockWise();

      if (flancoSubida(BTN_PARO)){
          state = S_PARO;
          break;
        
        }


        if (flancoSubida(BTN_ANTICLOCKWISE)){
          state = S_ANTICLOCKWISE;
          break;
        
        }
    
    break;


    case S_ANTICLOCKWISE:
    
    Serial.println("ANTICLOCKWISE");
    delay(500);
    AClockWise();
        
        
        if (flancoSubida(BTN_PARO)){
          state = S_PARO;
          break;
        
        }


        if (flancoSubida(BTN_ARRANQUE)){
          state = S_ARRANQUE;
          break;
        
        }
    
    break;
      
    
    
    }

}
