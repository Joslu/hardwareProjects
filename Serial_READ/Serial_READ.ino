#include <Stepper.h>

#define STEPS 48

// initialize the stepper library on pins 8 through 11:
Stepper stepper(STEPS, 8, 9, 10, 11);

void setup() {
  // set the speed at 60 rpm:
  stepper.setSpeed(100);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  // step one revolution  in one direction:
  Serial.println("clockwise");
  stepper.step(-48);
  delay(1000);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  stepper.step(48);
  delay(1000);

  

}
