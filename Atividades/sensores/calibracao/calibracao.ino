int led_vermelho = 13;
int led_verde = 12;
int led_amarelo = 11;
int pin_pot = A5;
int potMin = 1023;
int potMax = 0;

void setup() {
 Serial.begin(9600);
 pinMode(pin_pot, INPUT);
 pinMode(led_vermelho, OUTPUT);
 pinMode(led_verde, OUTPUT);
 pinMode(led_amarelo, OUTPUT);
 digitalWrite(led_vermelho,LOW);
 digitalWrite(led_verde,LOW);
 digitalWrite(led_amarelo,LOW);
 calibra();
 calibra();
 digitalWrite(led_amarelo, HIGH);
 Serial.print("potMin: ");
 Serial.println(potMin);
 Serial.print("potMax: ");
 Serial.println(potMax);
}

void calibra() { 
  blink(8);  
  int n;
  for(n=0;n<1000;n++){
    int pot = analogRead(pin_pot);

    if (pot < potMin){
      potMin = pot;
    } 
    if (pot > potMax) {
      potMax = pot;
    }
    delay(10);
  }
}

int Pmap(int d) { 
   int m = (int) (((d - potMin) * 255.) / (potMax - potMin));
   Serial.print("m: ");
   Serial.println(m);
   if (m < 0){
    return 0;
   } else if (m <= 255) {
    return m;
   } else {
    return 255;
   }
}

void loop() {
  int pot = analogRead(pin_pot);
  int pwm = Pmap(pot);
  analogWrite(led_verde,pwm);
  Serial.print("Pot: ");
  Serial.println(pot);
  Serial.print("PWM:: ");
  Serial.println(pwm);
  delay(1000);  
}

void blink(int times){
  for(int i=0;i<times;i++){
    digitalWrite(led_vermelho,HIGH);
    digitalWrite(led_amarelo,HIGH);
    delay(500);
    digitalWrite(led_vermelho,LOW);
    digitalWrite(led_amarelo,LOW);
    delay(500);
  }
}
