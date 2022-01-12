
#include <Stepper.h> //Libreria para el motor a pasos 


// Estados del sistema
#define S_MENU 0
#define S_OPCIONES 1


//Bototnes
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5


//Estado inicial
uint8_t state = S_MENU;



//Definimos constantes para el motor a pasos

//Número de pasos por revolución internos del motor
const float STEPS_PER_REV = 32;  
 
//Reducción incluida
const float GEAR_REV = 64;

//Número de pasos a la salida de la Reducción
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_REV;

//Definimos las variables 

//Número de pasos requeridos

int StepsR;
int Grados = 0;
int val;

//Se crea un objeto de la clase Stepper
//Usamos ls pines 8,9,10,11
//Conectados a ULN2003 IN1,IN2,IN3,IN4
//Los pines se ingresa en esta secuencia 1-3-2-4

Stepper steppermotor(STEPS_PER_REV,8,10,9,11);

//Definición de los pines que usaremos para los botones
uint8_t Boton[6] = {
    1,
    2,
    3,
    4,
    5,
    7
};

//Variable para el estado del boton
uint8_t Boton_State[6];



uint8_t flancoSubida(int btn) {
    //Esta función nos permite detectar un flanco de subida al presionar el botones

    uint8_t valor_nuevo = digitalRead(Boton[btn]);
    uint8_t result = Boton_State[btn]!=valor_nuevo && valor_nuevo == 1;
    Boton_State[btn] = valor_nuevo;
    return result;
}

void setup()
{
    Serial.begin(9600);
    pinMode(Boton[btnRIGHT],INPUT_PULLUP);
    pinMode(Boton[btnLEFT],INPUT_PULLUP);
    pinMode(Boton[btnSELECT],INPUT_PULLUP);
    pinMode(Boton[btnUP],INPUT_PULLUP);
    pinMode(Boton[btnNONE], INPUT_PULLUP);
    pinMode(Boton[btnDOWN],INPUT_PULLUP);
    pinMode(MODULO ,OUTPUT); 

    //Estado de los botones para detectar el flanco
    Boton_State[0] = HIGH;
    Boton_State[1] = HIGH;
    Boton_State[2] = HIGH;
    Boton_State[3] = HIGH;
    Boton_State[4] = HIGH;
    Boton_State[5] = HIGH;
    
}

void loop()
{
    switch(state){
        
        case S_MENU:
        
        
        break;

        case S_OPCIONES:
       
        

        break;

    }

}
   
            
