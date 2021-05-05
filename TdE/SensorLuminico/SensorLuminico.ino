/* AlturaPetiso
 * 
 * Arduino Nano, 1 HC-SR04, 1 rele,
 * 1 pestillo
 * 
 * 
 * Sputnik Ar
 * 21/08/30
 */

//DEFINES
#define RESPUESTA  100       //en cm

#define TIEMPO  1         //en segundos


#define LED          13
#define RELE         10


unsigned long filtrado = 0;

void setup() {
  Serial.begin(9600); 
  pinMode(OUTPUT, RELE);
  digitalWrite(RELE, HIGH);
  pinMode(OUTPUT, LED);
  digitalWrite(LED, LOW);
}

void loop() {
  boolean correcto = true;
  filtrado = millis();
  while(correcto && ((millis() - filtrado) < TIEMPO*1000)){
    int sensor = analogRead(A0);
    Serial.print("Lectura: ");
    Serial.println(sensor); //Imprime el valor de la lectura del canal A0 
    delay(200);
    if(sensor > RESPUESTA){}else{correcto = false;}}  

  if(correcto){
    digitalWrite(RELE,LOW);
    digitalWrite(LED,1);
    Serial.print("Resuelto");
    delay(TIEMPO*1000);  
  }else{
    digitalWrite(RELE,HIGH);
    digitalWrite(LED,0);     
  }
                       

}
