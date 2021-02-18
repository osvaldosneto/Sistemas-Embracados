int led_pin = 13;
int but_pin = 2;
int led_state = LOW;
int debounce_limit = 30;
unsigned long ultimo_acionamento = 0;

void interrupt_handler() {
 
  // Altera estado se o tempo de debounce acabou
  if (debounce()) {
      if (digitalRead(but_pin) == LOW) {
         led_state = HIGH; 
      } else {
         led_state = LOW;
      }
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


void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(but_pin, INPUT_PULLUP);
  // Ativa interrupação
  attachInterrupt(digitalPinToInterrupt(but_pin),interrupt_handler,CHANGE);
}

void loop() {
  digitalWrite(led_pin, led_state);
}
