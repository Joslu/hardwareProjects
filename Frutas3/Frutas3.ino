#define N 5
const int EchoPin = 43;
const int TriggerPin = 45;

#define CLlimones 4
#define CLTomates 5

#define S0 50
#define S1 52
#define S2 11
#define S3 10
#define sensorOut 12

/*+++++++++++++++++++++++*/
#define S_HOME 0
#define S_TRAINNING 1
#define S_TEST 2

uint8_t state = S_HOME ; // Estado Actual, lo colocamos en home 

#define BTN_HOME 0
#define BTN_TRAINNING 1
#define BTN_TEST 2
#define BTN_NEW 3

 
int centers[3][3];
int k1[N][3];
int k2[N][3];
int k3[N][3];
int Data[N][3];
int distance1=0;
int counter1 = 0;
int suma1=0;
int suma2=0;
int suma3=0;
int bgdata= 0;
int test_data[3]={0,0,0};
bool fl= false;

uint8_t getData();
void kmeans();
int ping(int,int);
void distances(bool);
uint8_t button[6] = {
  24,
  26,
  28,
  30
 };

uint8_t led[4] = {
  34,
  36,
  38,
  40
   
  };

uint8_t button_estate[6];

uint8_t flancoSubida(int btn) {
  uint8_t valor_nuevo = digitalRead(button[btn]);
  uint8_t result = button_estate[btn]!=valor_nuevo && valor_nuevo == 1;
  button_estate[btn] = valor_nuevo;
  return result;
}



void setup() {
  Serial.begin(9600);
  Serial.println("Inicio");
  Serial.println();

    for (int i=0; i <= 2; i++){
    for (int j=0; j <= 2; j++){
      randomSeed(millis());    // genera una semilla para aleatorio a partir de la función millis()
      centers[i][j] = random(255); //genera valores aleatorios 
    }
  }
  
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  pinMode(CLlimones, OUTPUT);
  pinMode(CLTomates,OUTPUT);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  
  pinMode(button[BTN_HOME],INPUT_PULLUP);
  pinMode(button[BTN_TEST],INPUT_PULLUP);
  pinMode(button[BTN_TRAINNING],INPUT_PULLUP);
  pinMode(button[BTN_NEW],INPUT_PULLUP);

  for(int i = 0; i < 4; i++){
      pinMode(led[i],OUTPUT);
      digitalWrite(led[i],LOW);
    }

  


  button_estate[0] = HIGH; //Resistencias como PULLUP
  button_estate[1] = HIGH; 
  button_estate[2] = HIGH; 
  button_estate[3] = HIGH; 

}

void loop() {

  switch(state){
    case S_HOME:/*Inicio Home*/
    Serial.println("STATE Home");
    delay(500);

    digitalWrite(led[0],HIGH);
    digitalWrite(led[1],LOW);
    digitalWrite(led[2],LOW);

    
      if (flancoSubida(BTN_TRAINNING)){
          state = S_TRAINNING;
        
          break;
            
        }

       if (flancoSubida(BTN_TEST)){
           state = S_TEST;
            break;
          
        }
        
      
        break; /*Fin Home*/
    
    case S_TRAINNING: /*Inicio Trainning*/

      
      Serial.println("STATE Trainning");
      delay(500);
      
      digitalWrite(led[0],LOW);
      digitalWrite(led[1],HIGH);
      digitalWrite(led[2],LOW);
      
       if (flancoSubida(BTN_HOME)){
           state = S_HOME;
            break;
        }

       if (flancoSubida(BTN_NEW)){
          state = S_TRAINNING;
          getData();
          kmeans();
          break;
        } 
    
    break;

    case S_TEST:
      
      Serial.println("STATE Test");
      delay(500);

      digitalWrite(led[0],LOW);
      digitalWrite(led[1],LOW);
      digitalWrite(led[2],HIGH);

       if (flancoSubida(BTN_HOME)){
           state = S_HOME;
            break;
          
        }

        if(flancoSubida(BTN_NEW)){
          int distance;
          distance = ping(TriggerPin,EchoPin);
          Serial.println(distance);
           getData();
           memcpy(test_data, Data, sizeof(Data));
          distances(false); 
          state = S_HOME;
      
          break;
          

        
          
          }

          break;
          
          }
        

        
   

}


uint8_t getData(){

  for(int a = 0; a < N ; a++){
     Data[a][0] = ping(TriggerPin,EchoPin);
     Data[a][1] = color();
     Data[a][3] = 1;
     
     Serial.println("Tenemos: ");
     Serial.print(Data[a][0]);
     Serial.print(" ");
      Serial.print(Data[a][1]);
       Serial.print(" ");
      Serial.print(Data[a][0]);
     Serial.println(); 
     digitalWrite(led[3],HIGH);
     delay(5000);
     digitalWrite(led[3],LOW);
      delay(5000);
    
    }

  }

int ping(int TriggerPin, int EchoPin) {
   long duration, distanceCm;
   
   digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(4);
   digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(TriggerPin, LOW);
   
   duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
   
   distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
   return distanceCm;
}

uint8_t color()
{
  uint8_t redColor = 0;
  uint8_t greenColor = 0;
  uint8_t redFrequency = 0;
  uint8_t greenFrequency = 0;
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  redFrequency = pulseIn(sensorOut, LOW);
  redColor = map(redFrequency, 47, 248, 255,0);

   // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  greenFrequency = pulseIn(sensorOut, LOW);
  greenColor = map(greenFrequency, 124, 424, 255, 0);

  if(redColor > greenColor ){
      return redColor;
  }

   if(greenColor > redColor){
    return greenColor;
  }
  }




void distances(bool flag){
  int a=0, b=0, c=0, q1, q2, q3, min1, min2, min3;
  k1[3][3]=0; k2[3][3]=0; k3[3][3]=0;
 for (int i=0; i < 20; i++){
    if (flag==true){
      q1=sqrt(pow(Data[i][0]-centers[0][0],2)+pow(Data[i][1]-centers[0][1],2)+pow(Data[i][2]-centers[0][2],2));
      q2=sqrt(pow(Data[i][0]-centers[1][0],2)+pow(Data[i][1]-centers[1][1],2)+pow(Data[i][2]-centers[1][2],2));
      q3=sqrt(pow(Data[i][0]-centers[2][0],2)+pow(Data[i][1]-centers[2][1],2)+pow(Data[i][2]-centers[2][2],2));
      min1=min(q1,q2);
      min2=min(q2,q3);
      min3=min(min1,min2);

       if (min3=q1){
        k1[a][0]= Data[i][0];
        k1[a][1]= Data[i][1];
        k1[a][2]= Data[i][2];
        a++;
       }
       else if (min3=q2){
        k2[b][0]= Data[i][0];
        k2[b][1]= Data[i][1];
        k2[b][2]= Data[i][2];
        b++;
       }
       else{
        k3[c][0]= Data[i][0];
        k3[c][1]= Data[i][1];
        k3[c][2]= Data[i][2];
        c++; 
       }
    }
    else{
      q1=sqrt(pow(test_data[0]-centers[0][0],2)+pow(test_data[1]-centers[0][1],2)+pow(test_data[2]-centers[0][2],2));
      q2=sqrt(pow(test_data[0]-centers[1][0],2)+pow(test_data[1]-centers[1][1],2)+pow(test_data[2]-centers[1][2],2));
      q3=sqrt(pow(test_data[0]-centers[2][0],2)+pow(test_data[1]-centers[2][1],2)+pow(test_data[2]-centers[2][2],2));
      min1=min(q1,q2);
      min2=min(q2,q3);
      min3=min(min1,min2);
       if (min3=q1){
        digitalWrite(CLlimones,HIGH);
       }
       else if (min3=q2){
        digitalWrite(CLTomates,HIGH);
       }
       else{
        digitalWrite(led[4],HIGH);
      }
    }
 }
 return;
}

void move_clusters(){
   for (int i = 0; i<=2; i++){
    for (int j = 0; j<20; j++){
      suma1 = suma1 + Data[j][0]; 
      suma2 = suma2 + Data[j][1];
      suma3 = suma3 + Data[j][2];
    }
    centers[i][0] =  suma1/20;
    centers[i][1] =  suma2/20;
    centers[i][2] =  suma3/20;
   }
   return;
}

void kmeans(){
  int centers_temp[3][3];
  int centers_temp2[3][3];
  memset(centers_temp, 0, sizeof (centers_temp));
  memset(centers_temp2, 0, sizeof (centers_temp2));
  do{
    distances(true);
    move_clusters();
    memcpy(centers_temp2, centers_temp, sizeof(centers_temp));
    memcpy(centers_temp, centers, sizeof(centers));   
  }while (centers_temp2 != centers);

  return;
}
