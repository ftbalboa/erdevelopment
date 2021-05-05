#include <VirtualWire.h>

int clk = 2;

int rst = 4;

int siguiente = 6;

int anterior = 8;

char senal = 'W';

int estado = 0;

void setup()
{
    Serial.begin(9600);  // abre el puerto de serie
    Serial.println("Receptor listo"); //Imprime "listo" en el monitor serial
    pinMode(13, OUTPUT); //configura el pin 13 como salida, se usara el led integrado.
    pinMode(clk,OUTPUT);
    digitalWrite(clk , LOW );
    pinMode(rst,OUTPUT);
    pinMode(anterior,OUTPUT);
    pinMode(siguiente,OUTPUT);
    pinMode(14, INPUT);
    vw_set_rx_pin(12);       //Configura el pin 12 como TX
    vw_set_ptt_inverted(true); //Requerido para DR3100
    vw_setup(4000);      //  Bits por segundo
    vw_rx_start();       // Inciar el receptor
}

void loop()
{
    digitalWrite(13, HIGH);      // Parpadeo para mostrar actividad
    uint8_t buf[VW_MAX_MESSAGE_LEN]; //Almacenar en buffer los datos recibidos
    uint8_t buflen = VW_MAX_MESSAGE_LEN; //Determina el numero de caracteres recibidos
    if (vw_get_message(buf, &buflen)) // Si hay un mensaje recibido ejecuta...
    {
  int i; 
        Serial.print("Rx: "); //imprime Rx en el monitor serial
  
  for (i = 0; i < buflen; i++)  //rutina para impresion del mensaje recibido
  {
            char c = (buf[i]); // guarda el caracter recibido para despues imprimirlo
 //           Serial.print(c); //imprime el caracter recibido en el monitor serial
 //     Serial.print(" "); //deja un espacio en el monitor serial

      if( c == 'P' && senal != c && estado == 0){

        Serial.print("entre p");

        digitalWrite(clk , HIGH );

        senal = c;

        estado++;
        
        }

      if( c == 'T' && senal != c && estado == 1){

        Serial.print("entre t");

        digitalWrite(clk , LOW );

        senal = c;

        estado++;
        
        }

      if( c == 'M' && senal != c && estado == 2){

   //     Serial.print("entre m");

        digitalWrite(clk , HIGH );

        delay (2000);

        digitalWrite(clk , LOW );

        senal = c;
      
        estado++;
                
        }

      if( c == 'R') {

        Serial.print("entre r"); 
        
        digitalWrite(rst , HIGH );

        digitalWrite(clk , LOW );

        delay (2000);

        digitalWrite(rst , LOW );

        senal = 'W';

        estado = 0;
        
        }

      if( c == 'S' /*&& senal != c*/){
        
        digitalWrite(siguiente , HIGH );

        delay (250);

        digitalWrite(siguiente , LOW );

        senal = c;
        
        }

      if ( c == 'X' /*&&  senal != c*/){
        
        digitalWrite(anterior , HIGH );

        delay (250);

        digitalWrite(anterior , LOW );

        senal = c;
        
        }
      
  }

//  Serial.println("");   // salto de linea monitor serial
    }
    
delay(125);                 // Pausa antes repetir el ciclo
digitalWrite(13, LOW);      // Parpadeo para mostrar actividad
delay(125);
// Pausa antes repetir el ciclo

//Serial.print(estado);

if(digitalRead(14)){
  
  
        senal = 'W';

        estado = 0;

        digitalWrite(clk , LOW );
  
  }
}
