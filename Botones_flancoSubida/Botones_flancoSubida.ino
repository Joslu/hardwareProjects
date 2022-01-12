#define BTN_MENU  0
#define BTN_EXIT  1
#define BTN_UP    2
#define BTN_DOWN  3

//Se definen los botones 
 uint8_t button[4] = {
    22,
    24,
    25,
    26
  };

uint8_t button_estate[4];
//Como parametro tenemos el boton 
uint8_t flancoSubida(int btn) {
  uint8_t valor_nuevo = digitalRead(button[btn]);
  uint8_t result = button_estate[btn]!=valor_nuevo && valor_nuevo == 1;
  button_estate[btn] = valor_nuevo;
  return result;
}



void setup() {
  Serial.begin(96000);
  pinMode(10,OUTPUT);
pinMode(button[BTN_MENU], INPUT_PULLUP);
  pinMode(button[BTN_EXIT], INPUT_PULLUP);
  pinMode(button[BTN_UP], INPUT_PULLUP);
  pinMode(button[BTN_DOWN], INPUT_PULLUP);
  
  button_estate[0] = HIGH;
  button_estate[1] = HIGH;
  button_estate[2] = HIGH;
  button_estate[3] = HIGH;

}

void loop() {
   if(flancoSubida(BTN_EXIT)) { // Transición BTN_EXIT
        Serial.println("Sí");
        
      }

      else
      Serial.println("NO");

      
}


