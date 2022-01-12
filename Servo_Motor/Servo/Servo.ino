#include <Servo.h>

Servo MyServo;

int pos = 0;

void setup(){
    MyServo.attach(11);

}

void loop(){
    for (pos = 0; pos <= 180; pos += 1){

        MyServo.write(pos);
        delay(15);
    }

    for (pos = 180; pos >= 0; pos -=1)
    {

        MyServo.attach(pos);
        delay(15);
    }

}
