#define S1 20
#define S2 19
#define S3 15
#define S4 14
#define S5 16

int value_eyes;
enum class EnemyPosition {ONLEFT, ONCENTER, ONRIGHT, NOTFOUND};
EnemyPosition enemy_position = EnemyPosition::NOTFOUND;

//Sensores
int cal_sp_l,cal_sp_r;
int sp_l,sp_r;

#define SENSOR_P1 21
#define SENSOR_P2 18



void setup(){

  Serial.begin(115200);
  pinMode(S1,INPUT);
  pinMode(S2,INPUT);
  pinMode(S3,INPUT);
  pinMode(S4,INPUT);
  pinMode(S5,INPUT);
  pinMode(SENSOR_P1,INPUT);
  pinMode(SENSOR_P2,INPUT);

  
  }

void loop(){

  cal_sp_l = 0;
  cal_sp_r = 0;
  cal_sp_l = Leer_Sensor_Piso(SENSOR_P1, cal_sp_l );
  cal_sp_r = Leer_Sensor_Piso(SENSOR_P2, cal_sp_r );
  Serial.print("SensoL = ");
  Serial.print(cal_sp_l);
  Serial.print(" ");
  Serial.print("SensoR = ");
  Serial.println(cal_sp_r);
  /*

Eyes();

switch (enemy_position) {
        case EnemyPosition::NOTFOUND:
           Serial.println("NOTFOUND");
           
          break;  
      
      case EnemyPosition::ONCENTER:
            Serial.println("ONCENTER");
         
          break;

      case EnemyPosition::ONLEFT:
             Serial.println("ONLEFT");
            
          break;

      case EnemyPosition::ONRIGHT:
             Serial.println("ONRIGHT");
          
              
          break;

    }*/
  }


 void Eyes(){

 value_eyes =  digitalRead(S1) + digitalRead(S2)*2 + digitalRead(S3)*4 + digitalRead(S4)*8 + digitalRead(S5)*16;
   
    switch(value_eyes)
  {
    case 30: enemy_position = EnemyPosition::ONRIGHT; break;
    case 15: enemy_position = EnemyPosition::ONLEFT;   break;
    case 29: enemy_position = EnemyPosition::ONRIGHT;  break; 
    case 23: enemy_position = EnemyPosition::ONLEFT;  break; 
    case 25: enemy_position = EnemyPosition::ONCENTER;  break; 
    case 19: enemy_position = EnemyPosition::ONCENTER;  break; 
    case 17: enemy_position = EnemyPosition::ONCENTER;  break;   
    default: enemy_position = EnemyPosition::NOTFOUND; 
  }
}

int Leer_Sensor_Piso(int pin, int cal)
{
  int PinState;
  int cnt;
  int sensor;
  
   pinMode(pin,OUTPUT);
   digitalWrite(pin, HIGH);
   delay(1);
  
   pinMode(pin,INPUT);

   cnt = 0;
   do{
     cnt ++;
     PinState = digitalRead(pin);
   }while(PinState == HIGH && cnt < 300);
     
   sensor = cnt - cal;
   return sensor;
}
