#include <MemoryFree.h>
#include "FunctionQueue.h"

int led_pin = 13;
int but_pin = 2;
int led_state = LOW;
unsigned int debounce_limit = 300;
unsigned long last = -1;


/* Configure Program Tasks */
FunctionQueue FQueue;

class LED_Function : public FunctionQueue::Function {
  public:
    LED_Function(int pin, bool state) : _pin(pin), _state(state) {}
    virtual ~LED_Function() {}

    void run() {
      led_state = _state;
      digitalWrite(_pin, led_state);
    }
    
  private:
    int _pin;
    bool _state;
};

class Delay_Function : public FunctionQueue::Function {
  public:
    Delay_Function(unsigned long ms) : _ms(ms) {}
    virtual ~Delay_Function() {}

    void run() {
      delay(_ms);
    }
    
  private:
    unsigned long _ms;
};


/* Program Logic */
void interrupt_handler()
{
    if (debounce()) {
        FQueue.push(new LED_Function(led_pin, digitalRead(but_pin)));
    }
}

int debounce()
{
    unsigned long now = millis();
    if( (now - last) > debounce_limit)
    {
      	last = now;
        return 1;
    }
    else {
        return 0;
    }
}


// Exemplo de como usar a fila para pistar um LED 3 vezes
void blink() {
    for(int i = 0; i < 3; i++) {
        FQueue.push(new LED_Function(led_pin, HIGH));
        FQueue.push(new Delay_Function(250));
        FQueue.push(new LED_Function(led_pin, LOW));
        FQueue.push(new Delay_Function(250));
    }
}

void setup()
{
    pinMode(led_pin, OUTPUT);
    pinMode(but_pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(but_pin), interrupt_handler, CHANGE);
    Serial.begin(9600);

    // Inicializar
    FQueue.push(new LED_Function(led_pin, led_state));
    blink();
}

void loop()
{
  // laço principal
  if(!FQueue.empty()) {
      FunctionQueue::Function * f = FQueue.pop();
      f->run();
      delete f;
  }
}
