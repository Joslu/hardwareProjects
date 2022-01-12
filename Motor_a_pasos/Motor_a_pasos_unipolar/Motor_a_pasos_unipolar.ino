#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <Stepper.h>

#define S_OFF 0
#define S_ON 1

#define BTN_ONOFF 0
#define BTN_AUMENTAR 1
#define BTN_180Positivo 2
#define BTN_180Negativo 3
#define Speed 700
uint8_t state = S_OFF;

#define MODULO 6

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
int Grados = 0;
int val;

//Se crea un objeto de la clase Stepper
//Usamos ls pines 8,9,10,11
//Conectados a ULN2003 IN1,IN2,IN3,IN4
//Los pines se ingresa en esta secuencia 1-3-2-4

Stepper steppermotor(STEPS_PER_REV,8,10,9,11);
LiquidCrystal_I2C lcd(0x27,16,2);


uint8_t Boton[4] = {
    3,
    4,
    5,
    7
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
    pinMode(Boton[BTN_AUMENTAR],INPUT_PULLUP);
    pinMode(Boton[BTN_180Negativo],INPUT_PULLUP);
    pinMode(Boton[BTN_180Positivo],INPUT_PULLUP);
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
        
        digitalWrite(MODULO,LOW);
        Serial.println("APAGADO");
        lcd.setCursor(0,0);
        lcd.print("Apagado");
        

            if(flancoSubida(BTN_ONOFF)){
                state = S_ON;
                break;
            }

        break;

        case S_ON:
       
        digitalWrite(MODULO,HIGH);
        Serial.println("ENCENDIDO");
        lcd.setCursor(0,0);
        lcd.print("Encendido");
     

        
        if (flancoSubida(BTN_AUMENTAR)){
                val = analogRead(0);
                val = map(val,0,1023,0,360);
                lcd.setCursor(0,0);
                lcd.print(val);

                digitalWrite(MODULO,HIGH);
                Serial.print("Avanza: ");
                Serial.print(Grados + 90);
                Serial.print(" grados");
                Serial.println();

                

                Grados = Grados + 90;
                StepsR = ((STEPS_PER_OUT_REV * Grados)/360);
                
                steppermotor.setSpeed(Speed);
                steppermotor.step(StepsR);
                delay(4000);

                if (Grados == 360){
                    Grados =0;
                    state = S_OFF;
                }
            

            }
            if (flancoSubida(BTN_ONOFF)){
                Grados = 0;
                Serial.println(Grados);
                state = S_OFF;
                break;

            }
        
            if (flancoSubida(BTN_180Positivo)){
                
                val = analogRead(0);
                val = map(val,0,1023,0,360);
                digitalWrite(MODULO,HIGH);
                Serial.print("Vuelta CW a ");
                Serial.print(val);
                Serial.print(" grados");
                Serial.println();

             StepsR = ((STEPS_PER_OUT_REV * val)/360);
                steppermotor.setSpeed(Speed);
                steppermotor.step(StepsR);
                delay(4000);
                state = S_OFF;

            }

            if (flancoSubida(BTN_180Negativo)){
                
                val = analogRead(0);
                val = map(val,0,1023,0,360);
                digitalWrite(MODULO,HIGH);
                Serial.print("Vuelta ACW a ");
                Serial.print(val);
                Serial.print(" grados");
                Serial.println();
                StepsR = -((STEPS_PER_OUT_REV * val)/360);
                steppermotor.setSpeed(Speed);
                steppermotor.step(StepsR);
                delay(4000);
                state = S_OFF;

            }


        break;

    }

}
   
            
