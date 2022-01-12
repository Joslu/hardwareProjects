// Programa practica 3

#define NUM_ENTRIES(ARRAY)      (sizeof(ARRAY) / sizeof(ARRAY[0]))

const uint8_t   BIT_OFF     = LOW;
const uint8_t   BIT_ON      = HIGH;

const uint8_t   pinsBITS[]  = {12,11, 10, 9, 8, 7, 6, 5,4,3};

const size_t    NUM_BITS    = NUM_ENTRIES(pinsBITS);


void setup()
{
    for ( size_t i = NUM_BITS; i--; )
    {
        pinMode(pinsBITS[i], OUTPUT);
    }

    Serial.begin(9600); 
}

void loop()
{
    int value = 125;
  

   // digitalWrite(13, HIGH);             

    for ( size_t i = 0; i < NUM_BITS; value >>= 1, i++ )
    {
        digitalWrite(pinsBITS[i], ((value & 1) ? BIT_ON : BIT_OFF));
    }

    delay(500);                       
}
