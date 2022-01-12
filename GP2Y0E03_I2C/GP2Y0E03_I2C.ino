#include <Wire.h>

#define SENSOR_ADRS   0x40              // GP2Y0E03のI2Cアドレス
#define DISTANCE_ADRS 0x5E              // Distance Value のデータアドレス
#define SENSOR1 6
#define SENSOR2 7


int menuselect;

void setup() { 
//Initialize serial and wait for port to open:
  Serial.begin(9600); 

      Wire.begin() ;                     // Ｉ２Ｃの初期化、マスターとする
     delay(1000) ;                      // 1秒後に開始

     pinMode(SENSOR1,OUTPUT);
     pinMode(SENSOR2,OUTPUT);

      pinMode(SENSOR1,LOW);
     pinMode(SENSOR2,LOW);

  
}

void loop()
{
  Menu();
  }



     
// 電源起動時とリセットの時だけのみ処理する関数
/*void setup()
{
     Serial.begin(9600) ;               // シリアル通信の初期化
     Wire.begin() ;                     // Ｉ２Ｃの初期化、マスターとする
     delay(1000) ;                      // 1秒後に開始

     pinMode(SENSOR1,OUTPUT);
     pinMode(SENSOR2,OUTPUT);
     
 

}
// 繰り返し実行されるメインの処理関数
void loop()
{

  
  Serial.println("Sensor1");
  LecturaSensor1(SENSOR1,SENSOR2);
  
  
  
  

 
 
    /* int  ans  ;
     byte c[2] ;


     digitalWrite(SENSOR2,HIGH);
     digitalWrite(SENSOR1,LOW);
     Serial.println("SENSOR 1: ON");
     Wire.beginTransmission(SENSOR_ADRS) ;        // 通信の開始処理
     Wire.write(DISTANCE_ADRS) ;                  // 距離値を格納したテーブルのアドレスを指定する
     ans = Wire.endTransmission() ;               // データの送信と終了処理
     if (ans == 0) {
          ans = Wire.requestFrom(SENSOR_ADRS,2) ; // GP2Y0E03にデータ送信要求をだし、2バイト受信する
          c[0] = Wire.read()  ;                   // データの11-4ビット目を読み出す
          c[1] = Wire.read()  ;                   // データの 3-0ビット目を読み出す
          ans = ((c[0]*16+c[1]) / 16) / 4 ;       // 取り出した値から距離(cm)を計算する
          Serial.print(ans) ;                     // シリアルモニターに表示させる
          Serial.println("cm") ;
     } else {
          Serial.print("ERROR NO.=") ;            // GP2Y0E03と通信出来ない
          Serial.println(ans) ;
     }
     delay(2000) ;                                 // 500ms後に繰り返す


     
}
*/


  void LecturaSensor(int SEL1,int SEL2){

    int  ans  ;
     byte c[2] ;

     digitalWrite(SEL1,HIGH);
     digitalWrite(SEL2,LOW);

     
     Wire.beginTransmission(SENSOR_ADRS) ;        // 通信の開始処理
     Wire.write(DISTANCE_ADRS) ;                  // 距離値を格納したテーブルのアドレスを指定する
     ans = Wire.endTransmission() ;               // データの送信と終了処理
     if (ans == 0) {
          ans = Wire.requestFrom(SENSOR_ADRS,2) ; // GP2Y0E03にデータ送信要求をだし、2バイト受信する
          c[0] = Wire.read()  ;                   // データの11-4ビット目を読み出す
          c[1] = Wire.read()  ;                   // データの 3-0ビット目を読み出す
          ans = ((c[0]*16+c[1]) / 16) / 4 ;       // 取り出した値から距離(cm)を計算する
          Serial.print(ans) ;                     // シリアルモニターに表示させる
          Serial.println("cm") ;
     } else {
          Serial.print("ERROR NO.=") ;            // GP2Y0E03と通信出来ない
          Serial.println(ans) ;
     }
     
     delay(1000) ;                                 // 500ms後に繰り返す
  
  
  }

void Menu() {
    Serial.println("menu_banner");
    for (;;) {
        switch (Serial.read()) {
            case '1': 
            
            Serial.println("SENSOR 1");
            LecturaSensor(SENSOR1, SENSOR2);; break;
            
            case '2': 
            Serial.println("SENSOR 2");
            LecturaSensor(SENSOR2, SENSOR1); break;  
            
            case '3': return;
            default: continue;  // includes the case 'no input'
        }
    }
}
