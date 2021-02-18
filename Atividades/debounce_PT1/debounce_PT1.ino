int led_pin = 13;
int but_pin = 2;
int pot_pin = A0;
int led_state = LOW;
int debounce_limit = 200;
unsigned long ultimo_acionamento = 0;

void interrupt_handler() {
  
  // Altera estado se o tempo de debounce acabou
  if (debounce()) {
      led_state = !led_state;
  }
  
}

bool debounce() {
  // Momento em que o botao foi acionado
  unsigned long botao_acionado = millis();
  
  // Passou o tempo de debounce, deve-se alterar o estado
  if ((botao_acionado - ultimo_acionamento) > debounce_limit) { 
      ultimo_acionamento = botao_acionado;
      return true;
  } else {
      return false;
  }

}

void blink() {
  // Escreve no pino do led o seu estado atual
  digitalWrite(led_pin, led_state);
}

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  pinMode(but_pin, INPUT_PULLUP);
  // Ativa interrupação
  attachInterrupt(digitalPinToInterrupt(but_pin),interrupt_handler,FALLING);
}

void loop() {
   blink();
   /*Serial.print("Valor pot.: ");
   unsigned int adc = analogRead(pot_pin);
   Serial.println(adc);
   unsigned long v = (5000*(unsigned long)adc) / 1024;
   Serial.print("Tensão (mV): ");
   Serial.println(v);
   delay(1000);*/
}
