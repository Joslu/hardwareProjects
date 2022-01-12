int Columnas[] = {2, 3, 4, 5, 6, 7, 8, 10, 11};
  
int Filas[] = {A0, 13, 12};
int RandFila; //Variable para fila aleatoria
int RandColumna; //Variable para columna aleatoria
char estado;

void setup() {
  int contador;
  Serial.begin(9600);  
  Serial.println("\tIngresa una tleca:");
  
 
  for (int contador = 0; contador < 9; contador++) {
    pinMode(Columnas[contador], OUTPUT); 
  }
 
  for (int contador = 0; contador < 3; contador++) {
    pinMode(Filas[contador], OUTPUT); 
  }
}
 
void loop() {
//RandLed();
Apagar();
if(Serial.available()>0){        // lee el bluetooth y almacena en estado
      estado = Serial.read();
  }


  if (estado == 'a'){
    Primera();
  }

   else if (estado == 'b'){
    Segunda();
  }
   
   else if (estado == 'c'){
    Tercera();
  }

   else if (estado == 'd'){
    Cuarta();
  }
   else if (estado == 'e'){
    Quinta();
  }
   else if (estado == 'f'){
    Sexta();
  }
   else if (estado == 'g'){
    Septima();
  }
  else if (estado == 'h'){
    Octava();
  }
  else if (estado == '0'){
    Apagar();
  }
  else
  RandLed();0
  
}

///Funcion del aparatato en estado normal 
void RandLed() {
  RandFila = random(0,3);
  RandColumna = random(0,9);
 
  digitalWrite(Filas[RandFila], HIGH);
  digitalWrite(Columnas[RandColumna], HIGH);
  delay(75);
 
  digitalWrite(Filas[RandFila], LOW);
  digitalWrite(Columnas[RandColumna], LOW);
  delay(50);
}

void Primera(){

  int i;
  digitalWrite(Filas[0],HIGH);

   for ( i =0; i <9; i ++){
          digitalWrite(Columnas[i],HIGH);
          delay(100);
   }
   
   for ( i =0; i <9; i ++){
          digitalWrite(Columnas[i],LOW);
          delay(100);
          
   }
  
}

void Segunda(){
     Line1(0,4,8);
     Line1(6,4,2);
  
}

void Tercera(){
  Line1(0,3,6);
  Line1(1,4,7);
  Line1(2,5,8);
  Line1(0,1,2);
  Line1(3,4,5);
  Line1(6,7,8);
  Line1(3,4,5);
  Line1(0,1,2);
  Line1(2,5,8);
  Line1(1,4,7);
  
}

void Cuarta(){
  Line2(0,1,3,4);
  Line2(4,5,7,8);
  
}




void Line1(int a, int b, int c){
 int i;
  digitalWrite(Filas[0],HIGH);

 
  digitalWrite(Columnas[a],HIGH);
  digitalWrite(Columnas[b],HIGH);
  digitalWrite(Columnas[c],HIGH);
  delay(75);

  digitalWrite(Columnas[a],LOW);
  digitalWrite(Columnas[b],LOW);
  digitalWrite(Columnas[c],LOW);
  delay(75);

}

void Line2(int a, int b, int c,int d){
 int i;
  digitalWrite(Filas[0],HIGH);

 
  digitalWrite(Columnas[a],HIGH);
  digitalWrite(Columnas[b],HIGH);
  digitalWrite(Columnas[c],HIGH);
  digitalWrite(Columnas[d],HIGH);
  delay(100);

  digitalWrite(Columnas[a],LOW);
  digitalWrite(Columnas[b],LOW);
  digitalWrite(Columnas[c],LOW);
  digitalWrite(Columnas[d],LOW);
  delay(100);

}

void Quinta(){

  int i;
  digitalWrite(Filas[0],HIGH);

   for ( i =9; i > -1; i --){
          digitalWrite(Columnas[i],HIGH);
          delay(100);
   }
   
   for ( i =9; i >-1; i --){
          digitalWrite(Columnas[i],LOW);
          delay(100);
          
   }
  
}

void Sexta(){
 
 int i;
 digitalWrite(Filas[0],HIGH);

 for ( i =1; i <9 ; i+=2){
          digitalWrite(Columnas[i],HIGH);
          delay(100);
   }
  for ( i =1; i <9; i+=2){
          digitalWrite(Columnas[i],LOW);
          delay(100);
   }  
 
}

void Septima(){
 
 int i;
 digitalWrite(Filas[0],HIGH);

 for ( i =0; i <9 ; i+=3){
          digitalWrite(Columnas[i],HIGH);
          delay(100);
   }
  for ( i =0; i <9; i+=3){
          digitalWrite(Columnas[i],LOW);
          delay(100);
   }  
 for ( i =1; i <9 ; i+=3){
          digitalWrite(Columnas[i],HIGH);
          delay(100);
   }
  for ( i =1; i <9; i+=3){
          digitalWrite(Columnas[i],LOW);
          delay(100);
   } 
   for ( i =2; i <9 ; i+=3){
          digitalWrite(Columnas[i],HIGH);
          delay(100);
   }
  for ( i =2; i <9; i+=3){
          digitalWrite(Columnas[i],LOW);
          delay(100);
   }   
}

void Octava(){
   int i;
 digitalWrite(Filas[0],HIGH);

 for ( i =0; i <9 ; i+=4){
          digitalWrite(Columnas[i],HIGH);
          delay(100);
   }
  for ( i =0; i <9; i+=4){
          digitalWrite(Columnas[i],LOW);
          delay(100);
   }  
  for ( i =2; i <9 ; i+=2){
          digitalWrite(Columnas[i],HIGH);
          digitalWrite(Columnas[8],LOW);
          delay(100);
   }
  for ( i =2; i <9; i+=2){
          digitalWrite(Columnas[8],LOW);
          digitalWrite(Columnas[i],LOW);
          delay(100);
   }    
  
}

void Apagar(){
  digitalWrite(Filas[0],LOW);
  
}

