#include <LiquidCrystal.h>
const int rs = 8, en = 9 , d4 = 4, d5 = 5, d6 = 6, d7 = 7;

LiquidCrystal lcd (rs, en, d4, d5, d6, d7);


void setup()
{
	lcd.begin(16, 2);
	lcd.print("Jose Luis");
	delay(1000);
}

void loop()
{
	
	for (int positionCounter= 0; positionCounter < 13; positionCounter++){
		lcd.scrollDisplayLeft();
		delay(150);
	}

	for (int positionCounter = 0; positionCounter < 29; positionCounter++){
		lcd.scrollDisplayRight();
		delay(150);
	}

	for(int positionCounter = 0; positionCounter < 16; positionCounter++){
	    lcd.scrollDisplayLeft();
	    delay(150);
	}

	delay(1000);
}

