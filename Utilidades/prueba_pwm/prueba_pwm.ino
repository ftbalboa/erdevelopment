#define PIN_PWM 8
boolean descenso = false;
int a = 0;
void setup() {
 pinMode(PIN_PWM , OUTPUT);
}

void loop() {
  analogWrite(PIN_PWM , a);
  if(descenso){a--; if(a == 0){descenso = false;}}else{a++; if(a == 255){descenso = true;}}
  delay(10);
}
