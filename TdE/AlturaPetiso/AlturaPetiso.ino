/* AlturaPetiso
 * 
 * Arduino Nano, 1 HC-SR04, 1 rele,
 * 1 pestillo
 * 
 * 
 * Sputnik Ar
 * 21/08/30
 */

//INCLUDES
#include <NewPing.h>

//DEFINES
#define ALTURA  160       //en cm

#define TIEMPO  1         //en segundos

#define CHANGUI 10        //en cm

#define LED          3
#define RELE         10
#define TRIGGER_PIN  12 
#define ECHO_PIN     11 
#define MAX_DISTANCE 200 

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

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
    int cm = sonar.ping_cm();
    Serial.print("Ping: ");
    Serial.print(sonar.ping_cm()); 
    Serial.println("cm");  
    delay(50);
    if(cm < ALTURA + CHANGUI && cm > ALTURA - CHANGUI){}else{correcto = false;}}  

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
