void setup() {
  //   Serial.begin(9600) ;          // 9600bpsでシリアル通信のポートを開きます
     pinMode(4, OUTPUT);  //definir pin como entrada
     digitalWrite(4, LOW);
  
 }
void loop() {
     int ans ;

     ans = IDMread(A5)  ;           // アナログピン０番のセンサー値を読込む
     ans = map(ans,0,1023,0,500) ; // 読込んだ値から電圧値に変換する(0-5V)
     ans = map(ans,50,220,50,4) ;  // 電圧値から距離に変換する(0.5-2.2V -> 50-4cm)

     if (ans < 12){
       digitalWrite(4, HIGH);
     }
     else
    {
      digitalWrite(4, LOW);
    }
       
    // Serial.print(ans-3) ;           // シリアルモニターに表示させる
     //Serial.println("cm") ;
     //delay(500) ;                  // 500ms後に繰り返す

   
 }
// 赤外線測距モジュールから読み込む処理
int IDMread(int PinNo) {
     long ans ;
     int i ;

     ans = 0 ;
     for (i=0 ; i < 100 ; i++) {
          ans  = ans + analogRead(PinNo) ;   // 指定のアナログピンから読取ります
     }
     return ans/100 ;                        // 100回の平均値を返します
}
