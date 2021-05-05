#include <VirtualWire.h>

int tx = 12;
int rst = 2;
int humo = 3;
int sig = 4;
int ant = 5;

void setup() {

    Serial.begin(9600);    // abre el puerto de serie
    Serial.println("Transmisor listo"); // Imprime "listo" en el monitor serial
    pinMode(13, OUTPUT); //configura el pin 13 como salida, se usara el led integrado.
   
    vw_set_tx_pin(12);          // Configura el pin 12 como TX
    vw_set_ptt_inverted(true);  // Requerido para DR3100
    vw_setup(4000);         // Bits por segundo

    pinMode(rst,INPUT);
    digitalWrite(rst,HIGH);
    pinMode(humo,INPUT);
    digitalWrite(humo,HIGH);
    pinMode(sig,INPUT);
    digitalWrite(sig,HIGH);
    pinMode(ant,INPUT);
    digitalWrite(ant,HIGH);    
}

void loop() {

  if(digitalRead(rst)==0){

    delay(100);
    if(digitalRead(rst)==0){
    char msg[] = "R";   // Mensaje a enviar
    vw_send((uint8_t *)msg, strlen(msg)); //Enviando...
    vw_wait_tx(); // espera hasta que el mensaje se haya enviado
    Serial.println("Transmitiendo...r"); // Imprime transmitiendo en el monitor serial

    delay(1000);
    }
    }

    if(digitalRead(sig)==0){

    delay(100);
    if(digitalRead(sig)==0){
    char msg[] = "A";   // Mensaje a enviar
    vw_send((uint8_t *)msg, strlen(msg)); //Enviando...
    vw_wait_tx(); // espera hasta que el mensaje se haya enviado
    Serial.println("Transmitiendo...s"); // Imprime transmitiendo en el monitor serial

    delay(1000);
    }
    }

      if(digitalRead(ant)==0){

    delay(100);
    if(digitalRead(ant)==0){
    char msg[] = "B";   // Mensaje a enviar
    vw_send((uint8_t *)msg, strlen(msg)); //Enviando...
    vw_wait_tx(); // espera hasta que el mensaje se haya enviado
    Serial.println("Transmitiendo...x"); // Imprime transmitiendo en el monitor serial

    delay(1000);
    }
    }

   if(digitalRead(humo)==0){

    delay (100);

    if(digitalRead(humo)==0){
    
    char msg[] = "B0.";   // Mensaje a enviar
    vw_send((uint8_t *)msg, strlen(msg)); //Enviando...
    vw_wait_tx(); // espera hasta que el mensaje se haya enviado
    Serial.println("Transmitiendo...h"); // Imprime transmitiendo en el monitor serial

    delay(1000);
    }
    }

}
