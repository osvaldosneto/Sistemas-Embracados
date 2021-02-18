/*
 * Solução para utilizar millis()
 * tratando o problema de overflow
 */
int led_pin = 7;
int ledState = LOW;
unsigned long prevMillis = 0;
unsigned long maxMillis = 4294967295;
const long interval = 1000;

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
}

void loop() {
  unsigned long currMillis = millis();
  if (prevMillis > currMillis) { // Verifica se ocorreu overflow
    prevMillis = maxMillis - prevMillis; // Diferença entre prevMillis e overflow
    blink(currMillis);
  } else {
    blink(currMillis);
  }
}

void blink(unsigned long currMillis) {
  if (currMillis - prevMillis >= interval) {
    prevMillis = currMillis;
    ledState = !ledState;
    digitalWrite(led_pin, ledState);
  }
}
