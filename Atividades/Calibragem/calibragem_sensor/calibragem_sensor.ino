int potMin = 1023; // = d min
int potMax = 0; // = d max

void setup() {
  
  Serial.begin(9600);
  analogReference(EXTERNAL);
  
}

void loop() {
  
  int pot = analogRead(A0); // sample pot
  Serial.print("Temperatura C:");
  Serial.println(Tmap(pot));
  Serial.print("Temperatura F:");
  Serial.println(celciusToFarenheit(Tmap(pot)));
  delay(1000);

}

float celciusToFarenheit(float c){
  float f = ((c * 9/5) + 32);
  return f;
}
  
float Tmap(int d) {
  float v = 3.3 * d / 1024.;
  if (v < 0.1)
    return -40.;
  else if (v <= 1.75)
    return 100. * v - 50.;
  else
    return 125.; // T u = 125◦ C
}
