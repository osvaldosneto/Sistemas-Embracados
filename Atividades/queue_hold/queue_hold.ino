#include "TimerOne.h"
#include "FunctionQueue.h"

int pwmctrl = 128; 
int pot_pin = A0;
int but_pin = 2;
int debounce_limit = 200;
int but_state = HIGH;
unsigned long ultimo_acionamento = 0;
FunctionQueue FQueue;

class Mostra_monitor : public FunctionQueue::Function {
  public:
    Mostra_monitor(unsigned int newpwm, unsigned long tensao) : _newpwm(newpwm), _tensao(tensao){}
    virtual ~Mostra_monitor() {}

    void run() {
      Serial.print("pwmctrl = ");
      Serial.println(pwmctrl);
      Serial.print("Tensao: ");
      Serial.print(_tensao);
      Serial.println(" mV");
      analogWrite(11, pwmctrl);
    }

    private:
      unsigned int _newpwm;
      unsigned long _tensao;
};

class Mostra_monitor_estatico : public FunctionQueue::Function {
  public:
    Mostra_monitor_estatico(unsigned int pwmctrl, unsigned long tensao) : _pwmctrl(pwmctrl), _tensao(tensao){}
    virtual ~Mostra_monitor_estatico() {}

    void run() {
      Serial.print("pwmctrl = ");
      Serial.println(_pwmctrl);
      Serial.print("Tensao: ");
      Serial.print(_tensao);
      Serial.println(" mV");
      analogWrite(11, _pwmctrl);
    }

    private:
      unsigned int _pwmctrl;
      unsigned long _tensao;
};

void interrupt_handler() {
 
  // Altera estado se o tempo de debounce acabou
  if (debounce()) {
      if (but_state == LOW) {
         //Timer1.detachInterrupt();
         Timer1.attachInterrupt(mostra_monitor_estatico,1000000);
      } else {
         Timer1.attachInterrupt(mostra_monitor,1000000);
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
  Serial.begin(9600);
  pinMode(but_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(but_pin),interrupt_handler,CHANGE);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(mostra_monitor);

  unsigned long tensao = (5000*(unsigned long)pwmctrl) / 256;
  
  //FQueue.push(new Mostra_monitor(pwmctrl,tensao));
  //FQueue.push(new Mostra_monitor_estatico(pwmctrl,tensao));
}

void mostra_monitor() {
  unsigned int newpwm = analogRead(pot_pin) >> 2;
  unsigned long tensao = (5000*(unsigned long)newpwm) / 256;
  pwmctrl = newpwm;
  FQueue.push(new Mostra_monitor(newpwm, tensao));
}

void mostra_monitor_estatico() {
  unsigned long tensao = (5000*(unsigned long)pwmctrl) / 256;
  FQueue.push(new Mostra_monitor_estatico(pwmctrl,tensao));
}

void loop() {
  but_state = digitalRead(but_pin); 
  if(!FQueue.empty()) {
      FunctionQueue::Function * f = FQueue.pop();
      f->run();
      delete f;
  }
}
