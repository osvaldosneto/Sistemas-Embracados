/*
 * Estudo PWM com buzzer
 */
int pwmctrl = 128; // 50%
int pot_pin = A5;
int buz_pin = 11;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int divisor[] = {1,8,32,64,128,256,1024,256,128,64,32,8};

  for(int i=0;i<(sizeof(divisor)/sizeof(divisor[0]));i++){
     setPwmFrequency(buz_pin, divisor[i]); 
     analogWrite(buz_pin, pwmctrl);
     delay(300);
  }
  
}

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
