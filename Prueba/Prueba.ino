
#define NUM_ENTRIES(ARRAY)      (sizeof(ARRAY) / sizeof(ARRAY[0]))

const uint8_t   LED_OFF     = LOW;
const uint8_t   LED_ON      = HIGH;

const uint8_t   pinsLEDS[]  = {3, 4, 5, 6, 7, 8, 9, 10, 11,12 };

const size_t    NUM_LEDS    = NUM_ENTRIES(pinsLEDS);


void setup()
{
    for ( size_t i = NUM_LEDS; i--; )
    {
        pinMode(pinsLEDS[i], OUTPUT);
    }

    Serial.begin(9600); 
}

void loop()
{
    int value   = analogRead(A3);
    float Voltaje = (5./1023)*value;

    Serial.print("Decimal = ");
    Serial.print(value);         
    Serial.print("\t Binario = ");      
    Serial.println(value, BIN);
    Serial.println("\t Voltaje = ");      
    Serial.println(Voltaje);

    digitalWrite(13, HIGH);             

    for ( size_t i = 0; i < NUM_LEDS; value >>= 1, i++ )
    {
        digitalWrite(pinsLEDS[i], ((value & 1) ? LED_ON : LED_OFF));
    }

    delay(500);                       
}