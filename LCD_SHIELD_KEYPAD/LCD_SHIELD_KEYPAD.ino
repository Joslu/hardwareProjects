

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 195)  return btnUP; 
 if (adc_key_in < 380)  return btnDOWN; 
 if (adc_key_in < 555)  return btnLEFT; 
 if (adc_key_in < 790)  return btnSELECT;   



 return btnNONE;  // when all others fail, return this...
}

void setup()
{

 pinMode(12,OUTPUT);
 pinMode(10,OUTPUT);
 pinMode(11,OUTPUT);

}
 
void loop()
{
          // move to the begining of the second line
 lcd_key = read_LCD_buttons();  // read the buttons

 switch (lcd_key)               // depending on which button was pushed, we perform an action
 {
    case btnLEFT:
     {
    
     digitalWrite(11,HIGH );
     break;
     }
   case btnUP:
     {
   
      digitalWrite(12, HIGH);
     break;
     }
   case btnDOWN:
     {

     digitalWrite(10, HIGH);
     break;
     }
   case btnSELECT:
     {
     digitalWrite(11, LOW);		
     digitalWrite(12, LOW);
     digitalWrite(10, LOW);		
    
     break;
     }
     case btnNONE:
     {
  		digitalWrite(11, LOW);		
     digitalWrite(12, LOW);
     digitalWrite(10, LOW);
     break;
     }
 }

}