#include <VirtualWire.h>

//PINOUT
int rx = 12;



void setup() {
  Serial.begin(9600);
  Serial.print("Inicio");
      //RX
    vw_set_rx_pin(rx);       //Configura el pin 12 como TX
    vw_set_ptt_inverted(true); //Requerido para DR3100
    vw_setup(4000);      //  Bits por segundo
    vw_rx_start();       // Inciar el receptor


}

void loop() {
     uint8_t buf[VW_MAX_MESSAGE_LEN]; //Almacenar en buffer los datos recibidos
    uint8_t buflen = VW_MAX_MESSAGE_LEN; //Determina el numero de caracteres recibidos
    if (vw_get_message(buf, &buflen)) // Si hay un mensaje recibido ejecuta...
    {
Serial.print("Rx: ");
int i;
  for (i = 0; i < buflen; i++)  //rutina para impresion del mensaje recibido
  {
            char c = (buf[i]); // guarda el caracter recibido para despues imprimirlo
            Serial.print(c); //imprime el caracter recibido en el monitor serial
      Serial.print(" "); //deja un espacio en el monitor serial
  }
        Serial.println("");   // salto de linea monitor serial
    }
    
  delay(125);                 // Pausa antes repetir el ciclo


}
