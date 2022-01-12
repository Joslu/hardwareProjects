#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <Stepper.h>

#define STEPS  2048   //Numero de pasos por revoluciones
LiquidCrystal_I2C lcd(0x27,16,2);

Stepper small_stepper(STEPS, 4, 5, 6, 7);


int lcd_key     = 0;
int adc_key_in  = 0;
int endStep = 1;
int startPos = 14336;
int endPos = 3300;
int minutes = 5;
long runtime = 0;
int rightLock = 0;
int leftLock = 28672;
int span = 0;
int stepDelay = 0;
int spanRemain = 0;
int motorPWR = 13;
int s;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
  
 
 // For V1.0 comment the other threshold and use the one below:
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 195)  return btnUP; 
 if (adc_key_in < 380)  return btnDOWN; 
 if (adc_key_in < 555)  return btnLEFT; 
 if (adc_key_in < 790)  return btnSELECT;   

 
 
 return btnNONE;  // when all others fail, return this...
}

void setup(){
  // Inicializar el LCD
  lcd.init();
  
  //Encender la luz de fondo.
  lcd.backlight();
pinMode(motorPWR, OUTPUT);
}

void loop(){
  digitalWrite(motorPWR, HIGH);
  
  lcd.setCursor(0,0);
  lcd.print("Angulo inicio L/R ");
  lcd.setCursor(0,1);
  lcd.print("Sel para confirmar");
  small_stepper.setSpeed(9);
  

  while(endStep){
     lcd_key = read_LCD_buttons();  // read the buttons
     switch (lcd_key)               // depending on which button was pushed, we perform an action
     {
       case btnRIGHT:
       {
         if (startPos > rightLock){
           small_stepper.step(-400);
           startPos = startPos - 400;
         }
         lcd.setCursor(0,1);
         lcd.print("pos:            ");
         lcd.setCursor(5,1);
         lcd.print(startPos);
         delay(250);
         break;
       }
     case btnLEFT:
       {
         if (startPos < leftLock){
           small_stepper.step(+400);
           startPos = startPos + 400;
         }
         lcd.setCursor(0,1);
         lcd.print("pos:            ");
         lcd.setCursor(5,1);
         lcd.print(startPos);
         delay(250);
         break;
       }
       case btnSELECT:
       {
         endStep = 0;
         delay(250);
         break;
       }
         case btnNONE:
       {
         break;
       }
     }
  }
  endStep = 1;
  lcd.setCursor(0,0);
  lcd.print("Angulo final L/R   ");
  lcd.setCursor(0,1);
  lcd.print("Sel para confirmar");

  endPos = startPos;
  
  while(endStep){
     lcd_key = read_LCD_buttons();  // read the buttons
     switch (lcd_key)               // depending on which button was pushed, we perform an action
     {
       case btnRIGHT:
       {
         if (endPos > rightLock){
           small_stepper.step(-400);
           endPos = endPos - 400;
         }
         lcd.setCursor(0,1);
         lcd.print("pos:            ");
         lcd.setCursor(5,1);
         lcd.print(endPos);
         delay(250);
         break;
       }
     case btnLEFT:
       {
         if (endPos < leftLock){
           small_stepper.step(+400);
           endPos = endPos + 400;
         }
         lcd.setCursor(0,1);
         lcd.print("pos:            ");
         lcd.setCursor(5,1);
         lcd.print(endPos);
         delay(250);
         break;
       }
       case btnSELECT:
       {
         endStep = 0;
         delay(250);
         break;
       }
         case btnNONE:
       {
         break;
       }
     }
  }
  endStep = 1;
  lcd.setCursor(0,0);
  lcd.print("Duracion: L/R   ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  while(endStep){
     lcd_key = read_LCD_buttons();  // read the buttons
     lcd.setCursor(0,1);
     lcd.print("    minutos");
     lcd.setCursor(0,1);
     lcd.print(minutes);
     delay(50);
     switch (lcd_key)               // depending on which button was pushed, we perform an action
     {
       case btnRIGHT:
       {
         if (minutes < 30) {
         minutes = minutes + 5;
         }
         else if (minutes < 120) {
         minutes = minutes + 15;
         }
         else if (minutes < 720) {
         minutes = minutes + 30;
         }
         delay(250);
         break;
       }
     case btnLEFT:
       {
         if (minutes > 0 && minutes < 35) {
         minutes = minutes - 5;
         }
         else if (minutes > 0 && minutes < 150) {
         minutes = minutes - 15;
         }
         else if (minutes > 0 && minutes < 725) {
         minutes = minutes - 30;
         }
         delay(250);
         break;
       }
       case btnSELECT:
       {
         endStep = 0;
         delay(250);
         break;
       }
         case btnNONE:
       {
         break;
       }
     }
  }
  
  runtime = (minutes * 60000);
  lcd.setCursor(0,0);
  lcd.print("Empezando");
  lcd.setCursor(0,1);
  lcd.print("    Minutos faltan");
  if (startPos > endPos){
    span = startPos - endPos;
    spanRemain = span;
    stepDelay = (runtime / span);
    small_stepper.step(span);
    while (spanRemain) {
      small_stepper.step(-1);
      runtime = (runtime - stepDelay);
      lcd.setCursor(0,1);
      lcd.print((runtime / 60000) + 1);
      spanRemain--;
      delay(stepDelay);
    }
      
  } else {
    span = endPos - span;
    startPos;
    spanRemain = span;
    stepDelay = (runtime / span);
    small_stepper.step(span * -1);
    while (spanRemain) {
      small_stepper.step(1);
      runtime = (runtime - stepDelay);
      lcd.setCursor(0,1);
      lcd.print((runtime / 60000) + 1);
      spanRemain--;
      delay(stepDelay);
    }
  }
  endStep = 0;
  while(1){
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("Program Complete");
    delay(500);
    lcd.setCursor(0,0);
    lcd.print("Program Complete");
    lcd.setCursor(0,1);
    lcd.print("                ");
    delay(500);
  }

}
  

