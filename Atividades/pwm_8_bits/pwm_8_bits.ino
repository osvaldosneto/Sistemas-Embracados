int pwmctrl = 128; // must be in [0, 255] for analogWrite
int pot_pin = A0;
void setup() {
  Serial.begin(9600);
}

void loop() {
  // Convertendo para 8 bits
  unsigned int newpwm = analogRead(pot_pin) >> 2;
  unsigned long tensao = (5000*(unsigned long)newpwm) / 256;
  
  if (newpwm != pwmctrl) {
    pwmctrl = newpwm;
    Serial.print("pwmctrl = ");
    Serial.println(pwmctrl);
    Serial.print("Tensao: ");
    Serial.print(tensao);
    Serial.println(" mV");
    analogWrite(11, pwmctrl);
  }

  delay(1200);
}
