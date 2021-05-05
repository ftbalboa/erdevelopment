#define PIN_INICIO  22
#define CANTIDAD    8
void setup() 
{
  Serial.begin(9600);
  for(int a = 0;a < CANTIDAD;a++){ 
    pinMode(PIN_INICIO+a , INPUT);
    digitalWrite(PIN_INICIO+a , HIGH);
  }
}

void loop() 
{
 Serial.println("--------NUEVA MEDICION----------"); 
 for(int a = 0;a < CANTIDAD;a++){
  Serial.print("PIN ");
  Serial.print(PIN_INICIO + a);
  Serial.print(": ");
  Serial.println(digitalRead(PIN_INICIO+a));
 } 
 delay(1000);  
}
