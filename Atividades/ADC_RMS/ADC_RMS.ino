/*
 * Média RMS de um ADC de 10 bits e 5V
 * 
 */
int pin_pot = A5;
int n = 10;
int level = 1024;
int max_voltage = 5000;

void setup() {
  Serial.begin(9600);
}

/*
 * Cálculo da média RMS
 */
unsigned long RMS(int medidas) {
  
  unsigned long acumulado = 0;
  for (int i = 0; i < medidas; i++) {
    unsigned int adc = analogRead(pin_pot); // Leitura analogica
    unsigned long valor_digital = (max_voltage*(unsigned long)adc) / 1024; // Conversao digital
    acumulado = acumulado + valor_digital*valor_digital; // Somatorio
  }
  // Media RMS
  unsigned long media = acumulado / medidas;
  unsigned long RMS = sqrt(media);
  return RMS;

}

void loop() {
  unsigned long val = 0;
  val = RMS(30);
  Serial.print("Digital: ");
  Serial.print(val);
  Serial.println(" mV");
  delay(3600);
}
