#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Stepper.h>

#define S_OFF 0
#define S_ON 1

#define BTN_ONOFF 0
#define BTN_CHECK 1

#define SENSOR1 2
#define SENSOR2 3

uint8_t state = S_OFF;

#define MODULO 6
#define ACTUADOR 2
//Definimos constantes

//Número de pasos por revolución internos del motor
const float STEPS_PER_REV = 32;  
 
//Reducción incluida
const float GEAR_REV = 64;

//Número de pasos a la salida de la Reducción
const float STEPS_PER_OUT_REV = (STEPS_PER_REV * GEAR_REV)/0.57;

//Definimos las variables 

//Número de pasos requeridos

int StepsR;
int Grados = 360;
int val;
int bandera1;
int bandera2;
int Se1;

//Se crea un objeto de la clase Stepper
//Usamos ls pines 8,9,10,11
//Conectados a ULN2003 IN1,IN2,IN3,IN4
//Los pines se ingresa en esta secuencia 1-3-2-4

Stepper steppermotor(STEPS_PER_REV,8,10,9,11);
LiquidCrystal_I2C lcd(0x27,16,2);


uint8_t Boton[4] = {
    3,
    4,
    A0,
    A1
};

uint8_t Boton_State[4];

uint8_t flancoSubida(int btn) {
    uint8_t valor_nuevo = digitalRead(Boton[btn]);
    uint8_t result = Boton_State[btn]!=valor_nuevo && valor_nuevo == 1;
    Boton_State[btn] = valor_nuevo;
    return result;
}

void setup()
{
    Serial.begin(9600);
    
    // Inicializar el LCD
    lcd.init();
  
    //Encender la luz de fondo.
    lcd.backlight();
    pinMode(Boton[BTN_ONOFF],INPUT_PULLUP);
    pinMode(ACTUADOR, OUTPUT);
    pinMode(Boton[BTN_CHECK],INPUT_PULLUP);
    pinMode(Boton[SENSOR1],INPUT_PULLUP);
    pinMode(Boton[SENSOR2],INPUT_PULLUP);
    pinMode(MODULO ,OUTPUT); 
    Boton_State[0] = HIGH;
    Boton_State[1] = HIGH;
    Boton_State[2] = HIGH;
    Boton_State[3] = HIGH;
  
    
}

void loop()
{
    switch(state){
        
        case S_OFF:
        //Se encuentra el sistema apagado
        digitalWrite(MODULO,LOW);
        digitalWrite(ACTUADOR,HIGH); //Apgado es activo bajo
        
        Serial.println("APAGADO");
        lcd.setCursor(0,0);
        lcd.print("Apagado");
        

            if(flancoSubida(BTN_ONOFF)){
                lcd.clear();
                state = S_ON;
                break;
            }

        break;

        case S_ON:

        //Se inicia el sistema
        digitalWrite(MODULO,HIGH);
        Serial.println("ENCENDIDO");
        lcd.setCursor(0,0);
        lcd.print("Encendido");
     
        Se1 = Read(A7)  ;           
        Se1 = map(Se1,0,1023,0,500) ; 
        Se1 = map(Se1,50,220,50,4) ;  
        Serial.println("Sensor 1");
        lcd.setCursor(0,1);
        lcd.print(Se1);
        delay(500);
        
        if (flancoSubida(BTN_CHECK)){
            lcd.clear();
            lcd.setCursor(0,0);
            Serial.println("Hola");
            lcd.print("Hola");
            

           if (Se1 < 15){
            
            digitalWrite(ACTUADOR,HIGH);
            Se1 = Read(A7)  ;           
            Se1 = map(Se1,0,1023,0,500) ; 
            Se1 = map(Se1,50,220,50,4) ;  
            lcd.setCursor(0,1);
            lcd.print(Se1);
            StepsR = -((STEPS_PER_OUT_REV * 180)/360);
            steppermotor.setSpeed(350);
            steppermotor.step(StepsR);
            Se1 = Read(A7)  ;           
            Se1 = map(Se1,0,1023,0,500) ; 
            Se1 = map(Se1,50,220,50,4) ;  
            lcd.setCursor(0,1);
            lcd.print(Se1);

            delay(3000);

                if (Se1 < 15){
                    digitalWrite(ACTUADOR,LOW);
                    delay(2000);
                    digitalWrite(ACTUADOR,HIGH);
                    StepsR = -((STEPS_PER_OUT_REV * 180)/360);
                    steppermotor.setSpeed(350);
                    steppermotor.step(StepsR);
                    digitalWrite(ACTUADOR,LOW);
                    delay(3000);
                    digitalWrite(ACTUADOR,HIGH);
                    delay(3000);
                    

                } 
            else{
                digitalWrite(ACTUADOR,LOW);
                Se1 = Read(A7)  ;           
                Se1 = map(Se1,0,1023,0,500) ; 
                Se1 = map(Se1,50,220,50,4) ;  
                lcd.setCursor(0,1);
                lcd.print(Se1);


                StepsR = ((STEPS_PER_OUT_REV * 180)/360);
                steppermotor.setSpeed(700);
                steppermotor.step(StepsR);
                delay(3000);

            }    

           }
            
           
            break;
            }

         
            
        if (flancoSubida(BTN_ONOFF)){
                lcd.clear();
                state = S_OFF;
                break;

            }
        if (flancoSubida(SENSOR1)){
                    lcd.clear();
                    lcd.setCursor(0,0);
                    lcd.print("Cerrado");
                    digitalWrite(ACTUADOR,LOW);
                    delay(5000);
                    
                    break;
                    }

        if (flancoSubida(SENSOR2)){
                    lcd.clear();
                    lcd.setCursor(0,0);
                    lcd.print("Encendido");
                    digitalWrite(ACTUADOR,HIGH);
                    delay(5000);
                    
                    break;
                    }

       
        break;

    }


}


int Read(int PinNo) {
     long ans ;
     int i ;

     ans = 0 ;
     for (i=0 ; i < 100 ; i++) {
          ans  = ans + analogRead(PinNo) ;  
     }
     return ans/100 ;                        
}
   
            
