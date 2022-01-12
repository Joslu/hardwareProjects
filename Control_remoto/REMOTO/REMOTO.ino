#include <IRremote.h>
#include <Servo.h>


int receptor = 9;
int led = 10;
IRrecv irrecv(receptor);
decode_results codigo; //OBJETO CODIGO DE CLASE decode_result, oriundo de IRremote.h
 
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // INICIA LA RECEPCIÓN

  pinMode(led, OUTPUT);
}
 
void loop()
{
 if (irrecv.decode(&codigo))
 {
Serial.println(codigo.value, HEX);

      if (codigo.value==0xFF9867)//CÓDIGO DEL NÚMERO CERO PARA ACTIVAR LED
      {
         digitalWrite(led,HIGH);
      }

      if (codigo.value==0xFFA25D)//CÓDIGO DEL NÚMERO UNO PARA DESACTIVAR LED
      {
         digitalWrite(led,LOW);
      }

   

       
    
delay(500);
irrecv.resume();

 }
}


