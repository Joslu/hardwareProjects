#include "arduino.h"
#include <stdio.h>     
#include <stdlib.h>  
#include <time.h> 

class Trainer {
  
  float inputs[];
  int answer; 
  
  Trainer(float x, float y, int a) {
    float inputs[3];
    inputs[0] = x;
    inputs[1] = y;
    inputs[2] = 1;
    answer = a;
  }
};
