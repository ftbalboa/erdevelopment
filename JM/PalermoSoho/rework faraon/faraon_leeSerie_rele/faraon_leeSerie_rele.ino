/* Servidor Faraon
 * 
 * Arduino NANO,   1 reles
 * 1 RX
 * 
 * Sputnik 5/1/2
 */



 //INCLUDES
#include <Wire.h>

//DEFINES
#define SPRINT      true
#define NEED_REPOSO true

#define   RELE       2


#define DS          200


//CONSTANTES
const int N_INPUTS = 1;
const int INPUTS[N_INPUTS] = {8};
const int INPUTS_ISTATE[N_INPUTS] = {1};
const int N_OUTPUTS = 1;
const int OUTPUTS[N_OUTPUTS] = {RELE};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1};


//VARIABLES
unsigned long contador_tiempo = 0;

char recibi = 0;



//OBJETOS


//NO EDITABLE
unsigned long timer_print = 0;

////////////////////////////////////SETUP///////////////////////////////
//NO EDITABLE
void setup() {
  delay(1000);
  if(SPRINT){Serial.begin(9600);} 
//declara entradas
  for(int a = 0;a < N_INPUTS;a++){ 
    pinMode(INPUTS[a] , INPUT);
    digitalWrite(INPUTS[a] , INPUTS_ISTATE[a]);
  }
//declara salidas
  for(int a = 0;a < N_OUTPUTS;a++){ 
    pinMode(OUTPUTS[a] , OUTPUT);
    digitalWrite(OUTPUTS[a] , OUTPUTS_ISTATE[a]);
  }

//EDITABLE 

}

///////////////////////////////////////LOOP//////////////////////////////////////////
void loop() {
  levanta();
}

////////////////////////////////////////FUNCIONES///////////////////////////////////
//EDITABLE


void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
   timer_print = millis();
    }
  }


void levanta()
{
  while(Serial.available()){
    char inp = Serial.read();
    Serial.print(inp);
    if(inp == '3'){digitalWrite(RELE,0);}
    }
}




//NO EDITABLE
//comprueba el estado de un sensor
boolean check (boolean cual, int entrada, int ds)
{
  boolean resu = false;
  int contador = 0;  
  if(cual){ while(digitalRead(entrada) == 1 && resu == false){contador++;if(contador == ds){resu = true;}}
  }else{    while(digitalRead(entrada) == 0 && resu == false){contador++;if(contador == ds){resu = true;}}}  
  return resu; 
}
