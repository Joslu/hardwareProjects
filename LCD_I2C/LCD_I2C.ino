#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27,16,2);  //
byte cuerpo[8] = {
B01110,
B01110,
B00100,
B11111,
B00100,
B01010,
B10001,
B00000,
};
void setup() {
  // Inicializar el LCD
  lcd.init();
  
  //Encender la luz de fondo.
  lcd.backlight();
  lcd.createChar (7,cuerpo);
  // Escribimos el Mensaje en el LCD.
  lcd.setCursor(15,0);
  lcd.print("Jelou Eva :)");
  lcd.setCursor(24,1);
  lcd.write (byte (7));
}

void loop() {
   // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
   lcd.scrollDisplayLeft(); 
  delay(500);
}
