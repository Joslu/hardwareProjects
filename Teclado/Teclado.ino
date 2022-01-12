#include <Keypad.h>            // Prog_19_1
const byte Filas = 4;          //Cuatro filas
const byte Cols = 4;           //Cuatro columnas

byte Pins_Filas[] = {7, 6, 5, 4};     //Pines Arduino para las filas
byte Pins_Cols[] = { 3, 2, 10, 8};     // Pines Arduinopara las columnas
char Teclas [ Filas ][ Cols ] =
          {
              {'1','2','3','A'},
              {'4','5','6','B'},
              {'7','8','9','C'},
              {'*','0','#','D'}
          };
Keypad myKeypad = Keypad(makeKeymap(Teclas), Pins_Filas, Pins_Cols, Filas, Cols);

int Primero = 13;
 
void setup()
        {            
          Serial.begin(9600); 
          pinMode(Primero,OUTPUT);
       
          
          }

void loop()
 {       char pulsacion = myKeypad.getKey() ;
         if (pulsacion != 0)              // Si el valor es 0 es que no se
          digitalWrite(Primero,HIGH);
          delay(100);
          digitalWrite(Primero,LOW);
                    Serial.println(pulsacion);   // se ha pulsado ninguna tecla
                  
             
        }

void Encender()
{
   int i;
   for (i=0; i < 5; i++){
    
   }
}

        
