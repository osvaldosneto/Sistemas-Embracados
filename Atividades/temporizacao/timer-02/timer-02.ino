#include "TimerOne.h"

int pin_pot = A5;
int c = 0;
int tempo_leitura = 600; // 1s = 10 x 100ms
int valores[10] = {0,0,0,0,0,0,0,0,0,0};
String legenda[10] = {"   0-500 "," 500-1000","1000-1500","1500-2000","2000-2500","2500-3000"
                      ,"3000-3500","3500-4000","4000-4500","4500-5000"};

void setup() {
  Serial.begin(9600);
  Timer1.attachInterrupt(leitura);
  Timer1.initialize(100000); // 100ms
}

void loop() {}

/* Realiza a leitura da entrada analógica*/
void leitura() {
  
   if (c<tempo_leitura){
     unsigned int adc = analogRead(pin_pot); // Leitura analogica
     unsigned long v = (5000*(unsigned long)adc) / 1024; // Conversao digital
    
     if ((v>0)&&(v<500)){
       valores[0] = valores[0] + 1;
     } else if ((v>500)&&(v<1000)) {
        valores[1] = valores[1] + 1;
     } else if ((v>1000)&&(v<1500)) {
       valores[2] = valores[2] + 1;
     } else if ((v>1500)&&(v<2000)) {
       valores[3] = valores[3] + 1;
     } else if ((v>2000)&&(v<2500)) {
       valores[4] = valores[4] + 1;
     } else if ((v>2500)&&(v<3000)) {
       valores[5] = valores[5] + 1;
     } else if ((v>3000)&&(v<3500)) {
       valores[6] = valores[6] + 1;
     } else if ((v>3500)&&(v<4000)) {
       valores[7] = valores[7] + 1;
     } else if ((v>4000)&&(v<4500)) {
       valores[8] = valores[8] + 1;
     } else if ((v>4500)&&(v<5000)) {
       valores[9] = valores[9] + 1;
     } else {
       Serial.println("erro");
     }
     c++;
   } else {
    c = 0;
    histograma();
   }
   
}

/* Plota Histograma*/
void histograma() {
  Serial.println("        Histograma");
  for(int i=0; i<10; i++){
    Serial.print(legenda[i]);
    Serial.print(" | ");
    for (int j=0;j<valores[i];j++) {
      Serial.print("+");
    }
    Serial.print(" ");
    Serial.print("(");
    Serial.print(valores[i]);
     Serial.print(")");
    Serial.println();
    valores[i] = 0;
  }
  Serial.println();
}
