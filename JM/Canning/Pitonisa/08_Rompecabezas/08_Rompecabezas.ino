/*  ROMPECABEZA_08
 * 
 * MEGA, DFPLAYER, IMANES, OPTO Y RELES
 * 
 */
 
//INCLUDES
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
 
//EDITABLE
#define SPRINT      false
#define NEED_REPOSO false
#define VALVU    22
#define RELE1    23
#define RELE2    24
#define OPTO     25

#define DS       30


const int N_INPUTS = 1;
const int INPUTS[N_INPUTS] = {VALVU};
const int INPUTS_ISTATE[N_INPUTS] = {1};
const int N_OUTPUTS = 3;
const int OUTPUTS[N_OUTPUTS] = {RELE1,RELE2, OPTO};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,1,1};



//OBJETOS


//NO EDITABLE
boolean reposo = false;
boolean activo = false;
boolean resuelto = false;
unsigned long timer_print = 0;
////////////////////////////////////SETUP///////////////////////////////
//NO EDITABLE
void setup() {
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
//si necesita reposo
  if(NEED_REPOSO){reposo=true;activo=false;resuelto=false;}else{reposo=false;activo=true;resuelto=false;}
//EDITABLE
}

///////////////////////////////////////LOOP//////////////////////////////////////////
void loop() {
  if_reposo();
  if_activo();
  if_resuelto();
  showme();
}

////////////////////////////////////////FUNCIONES///////////////////////////////////
//EDITABLE
void if_reposo()
{
  if(reposo){
  }
}

void if_activo()
{
  if(activo){
    if(check(0,VALVU,DS)){delay(1000);if(check(0,VALVU,DS)){activo=false;resuelto=true;}}
  }
}

void if_resuelto()
{
  if(resuelto){
    digitalWrite(RELE1,LOW);
    digitalWrite(OPTO,LOW);
  }
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    Serial.print("Valvulas: ");
    Serial.println(check(0, VALVU ,DS));
    timer_print = millis();
    }
  }

//NO EDITABLE
//comprueba el estado de un sensor
boolean check (boolean cual, int entrada, int ds)
{
  boolean resu = false;
  int contador = 0;  
  if(cual){ while(digitalRead(entrada) == 1 && resu == false){delay(ds);contador++;if(contador == 5){resu = true;}}
  }else{    while(digitalRead(entrada) == 0 && resu == false){delay(ds);contador++;if(contador == 5){resu = true;}}}  
  return resu; 
}
