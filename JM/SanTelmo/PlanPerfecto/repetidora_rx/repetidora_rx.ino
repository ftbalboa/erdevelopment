#include <VirtualWire.h>

int count;

/*
MENSAJES A REPETIR
R = reset
P = puerta
T = telefono
M = mascaras
A = finala
B = finalb
H = humo
S = siguiente 
*/

//pinModes

static int b1 = 2;
static int b2 = 4;
static int b3 = 6;
static int clk = 8;
static int rx = 12;

char ant = 'N';

void setup()
{
    Serial.begin(9600);	// abre el puerto de serie
    Serial.println("Receptor listo"); //Imprime "listo" en el monitor serial
    pinMode(13, OUTPUT); //configura el pin 13 como salida, se usara el led integrado.
    
    vw_set_rx_pin(rx);       //Configura el pin 12 como TX
    vw_set_ptt_inverted(true); //Requerido para DR3100
    vw_setup(4000);	     //  Bits por segundo
    vw_rx_start();       // Inciar el receptor
    
    //pinModes
    
    pinMode(b1,OUTPUT);
    pinMode(b2,OUTPUT);
    pinMode(b3,OUTPUT);
    pinMode(clk,OUTPUT);
    digitalWrite(clk,LOW);
    
    
}

void loop() {
    uint8_t buf[VW_MAX_MESSAGE_LEN]; //Almacenar en buffer los datos recibidos
    uint8_t buflen = VW_MAX_MESSAGE_LEN; //Determina el numero de caracteres recibidos
    if (vw_get_message(buf, &buflen)) // Si hay un mensaje recibido ejecuta...
    {
	int i; 
       	Serial.print("Rx: "); //imprime Rx en el monitor serial
	
	for (i = 0; i < buflen; i++)  //rutina para impresion del mensaje recibido
	{
            char c = (buf[i]); // guarda el caracter recibido para despues imprimirlo
            
            if (ant == c){}else{
            
            switch(c){
            
              case 'R':
              
              digitalWrite(b1,LOW);
              digitalWrite(b2,LOW);
              digitalWrite(b3,LOW);
              
              digitalWrite(clk,HIGH);
              delay (2000);
              digitalWrite(clk,LOW);
              
              ant = 'R';
              
              break;
              
              case 'P':
              
              digitalWrite(b1,LOW);
              digitalWrite(b2,LOW);
              digitalWrite(b3,HIGH);
              
              digitalWrite(clk,HIGH);
              delay (2000);
              digitalWrite(clk,LOW);
              
              ant = 'P';
              
              break;
              
              case 'T':
              
              digitalWrite(b1,LOW);
              digitalWrite(b2,HIGH);
              digitalWrite(b3,LOW);
              
              digitalWrite(clk,HIGH);
              delay (2000);
              digitalWrite(clk,LOW);
              
              ant = 'T';
              
              break;
              
              case 'M':
              
              digitalWrite(b1,LOW);
              digitalWrite(b2,HIGH);
              digitalWrite(b3,HIGH);
              
              digitalWrite(clk,HIGH);
              delay (2000);
              digitalWrite(clk,LOW);
              
              ant = 'M';
              
              break;
              
              case 'A':
              
              digitalWrite(b1,HIGH);
              digitalWrite(b2,LOW);
              digitalWrite(b3,LOW);
              
              digitalWrite(clk,HIGH);
              delay (2000);
              digitalWrite(clk,LOW);
              
              ant = 'A';
              
              break;
              
              case 'B':
              
              digitalWrite(b1,HIGH);
              digitalWrite(b2,LOW);
              digitalWrite(b3,HIGH);
              
              digitalWrite(clk,HIGH);
              delay (2000);
              digitalWrite(clk,LOW);
              
              ant = 'B';
              
              break;
              
              case 'H':
              
              digitalWrite(b1,HIGH);
              digitalWrite(b2,HIGH);
              digitalWrite(b3,LOW);
              
              digitalWrite(clk,HIGH);
              delay (2000);
              digitalWrite(clk,LOW);
              
              ant = 'H';
              
              break;

              case 'S':
              
              digitalWrite(b1,HIGH);
              digitalWrite(b2,HIGH);
              digitalWrite(b3,HIGH);
              
              digitalWrite(clk,HIGH);
              delay (2000);
              digitalWrite(clk,LOW);
              
              ant = 'S';
              
              break;
            
            }
            }
            Serial.print(c); //imprime el caracter recibido en el monitor serial
	    Serial.print(" "); //deja un espacio en el monitor serial
	}
        count++;  //incrementa contador
        Serial.print(count);  //imprime el contador en el monitor serial
	Serial.println("");   // salto de linea monitor serial
    }
    
delay(125);                 // Pausa antes repetir el ciclo

delay(125);                 // Pausa antes repetir el ciclo
}
