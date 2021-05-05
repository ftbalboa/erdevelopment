#include <VirtualWire.h>

int tx = 12;

void setup() {
  
            vw_set_tx_pin(tx);          // Configura el pin 12 como TX (SETEA TX)
            vw_set_ptt_inverted(true);  // Requerido para DR3100
            vw_setup(4000);          // Bits por segundo 

}

void loop() {

            char msg[] = "P";   // Mensaje a enviar
            vw_send((uint8_t *)msg, strlen(msg)); //Enviando...
            vw_wait_tx(); // espera hasta que el mensaje se haya enviado

            delay(150);

}
