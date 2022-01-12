/*
 * DRV8833_Test
 * Simple test for the DRV8833 library.
 * The DRV8833 is a dual motor driver carrier made by Pololu.
 * You can find it here: https://www.pololu.com/product/2130
 *
 * Attach the positive wire of a motor to the Aout1 and the negative
 * wire to the Aout2 pins on the DRV8833.
 * Attach the Arduino's ground to the one of the GND pins on the DRV8833.
 * Attach a 9V battery's positive connection to the Vin pin
 * on the DRV8833, and the negative connection to one of the GND pins.
 * 
 * Created March 16, 2015, by Aleksandr J. Spackman.
 */

#include <DRV8833.h>

// Create an instance of the DRV8833:
DRV8833 driver = DRV8833();

// Pin numbers. Replace with your own!
// Attach the Arduino's pin numbers below to the
// Ain1 and Ain2 DRV8833 pins.
const int inputA1 = 10, inputA2 = 9;

void setup() {
  // put your setup code here, to run once:

  pinMode(4,OUTPUT);
  // Attach a motor to the input pins:
  driver.attachMotorA(inputA1, inputA2);


}

void loop() {
  // put your main code here, to run repeatedly:
  

  // Put the motor in forward:
  driver.motorAForward();
  // Wait to see the effect:
  digitalWrite(4, HIGH);
  delay(500);
  
  // Pause the motor for stability:
  driver.motorAStop();
  

  // Put the motor in reverse:
  driver.motorAReverse();
  // Wait to see the effect:
   digitalWrite(4, LOW);
  delay(500);

  // Stop the motor:
  driver.motorAStop();
  // Wait to see the effect:
  delay(500);

}
