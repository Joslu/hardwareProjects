#define SHARP1 A3
#define SHARP2 A4
#define SHARP3 A5


void setup() {
     Serial.begin(9600) ;          
 }
void loop() {
     int SIzq, SDer, SCen;

     SIzq = ReadS(SHARP1)  ;           
     SIzq = map(SIzq,0,1023,0,500) ; 
     SIzq = map(SIzq,50,220,50,4) ;  
     Serial.println("Sensor 1");
     Serial.print(SIzq) ;           
     Serial.println("cm") ;
     delay(10);

     SDer = ReadS(SHARP3)  ;           
     SDer = map(SIzq,0,1023,0,500) ; 
     SDer = map(SIzq,50,220,50,4) ;  
     Serial.println("Sensor 1");
     Serial.print(SDer) ;           
     Serial.println("cm") ;
     delay(10);

     
     SCen = ReadS(SHARP2)  ;           
     SCen = map(SIzq,0,1023,0,500) ; 
     SCen = map(SIzq,50,220,50,4) ;  
     Serial.println("Sensor 1");
     Serial.print(SCen) ;           
     Serial.println("cm") ;
     delay(10);

 }

int ReadS(int PinNo) {
     long ans ;
     int i ;

     ans = 0 ;
     for (i=0 ; i < 100 ; i++) {
          ans  = ans + analogRead(PinNo) ;  
     }
     return ans/100 ;                        
}



