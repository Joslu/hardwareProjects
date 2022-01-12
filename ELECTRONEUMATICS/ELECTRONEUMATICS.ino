#define S_A 0 //A+
#define S_B 1 //A-

uint8_t state = S_B; //Estado actual lo colocamos en paro

#define SENSOR1 0
#define SENSOR2 1


#define IN1 3

uint8_t sensor[2] = {
  5,
  6 
};

uint8_t sensor_state[2];

uint8_t flancoSubida(int btn) {
    uint8_t valor_nuevo = digitalRead(sensor[btn]);
    uint8_t result = sensor_state[btn]!=valor_nuevo && valor_nuevo == 1;
    sensor_state[btn] = valor_nuevo;
    return result;
}

void Activar_Rele(){
  digitalWrite(IN1,HIGH);
  delay(2000);
  }

void Desactivar_Rele(){
  digitalWrite(IN1,LOW);
  delay(2000);
  }


  
void setup() {

  Serial.begin(9600);
  Serial.println("INICIO");
  Serial.println();
  
  pinMode(sensor[SENSOR1],INPUT_PULLUP);
  pinMode(sensor[SENSOR2],INPUT_PULLUP);

  pinMode(IN1,OUTPUT);
  digitalWrite(IN1,HIGH);

  sensor_state[0] = HIGH;
  sensor_state[1] = HIGH;

}

void loop() {
  switch(state){
    
    case S_B:

    Serial.println("Estado A+");
    delay(500);
    //state = S_B;
    Activar_Rele();
    if(flancoSubida(SENSOR2)){
        state = S_A;
        break;
      }

     
     case S_A:
     Serial.println("Estado A-");
     delay(500);
     //state = S_A;
     Desactivar_Rele();
     if(flancoSubida(SENSOR1)){
        state = S_B;
      }
    break;

     if(flancoSubida(SENSOR2)){
        state = S_A;
      }
    break;
    
    
    
    }
  
}
