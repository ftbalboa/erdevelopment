/* Ataud Main Nosferatu
 * 
 * Arduino MEGA,2 canales UNL2003, DFPLAYER, UN RELE, UN RS Y dos palancas
 * 
 * Main del juego Nosferatu, al darle play a una palanca
 * comienza un audio y se empieza a dimerizar canal 1 hasta apagar
 * a los 5 min se prende la luz de canal 2, si antes de los 15 se cierra RS
 * se abre rele y se escucha audio 2, sino audio 3, se resetea con un power up
 * 
 * Sputnik 18/4/19
 */

//INCLUDES
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h" 
 
//EDITABLE
#define SPRINT      false
#define NEED_REPOSO true
#define DFTX        3
#define DFRX        2
#define PAL1        4
#define PAL2        5
#define RS          6
#define UNL1        7
#define UNL2        8
#define RELE        23

#define DS  20

#define MINUTOS     15
#define TIEMPO_VAMPIRO     5

const int N_INPUTS = 3;
const int INPUTS[N_INPUTS] = {RS,PAL1,PAL2};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1};
const int N_OUTPUTS = 3;
const int OUTPUTS[N_OUTPUTS] = {UNL1,UNL2,RELE};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {0,0,0};

unsigned int tiempo_restante = MINUTOS * 60;
unsigned long contador_tiempo = 0;

SoftwareSerial mySoftwareSerial(DFRX, DFTX);    // RX, TX
DFRobotDFPlayerMini myDFPlayer; 

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
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial)) {}
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
    if(check(0,PAL1,DS)){activo = true;reposo = false;digitalWrite(UNL1,HIGH);myDFPlayer.play(1);}
  }
}

void if_activo()
{
  if(activo){
    if(check(0,RS,DS) || check(0,PAL2,DS)){activo = false;resuelto = true;myDFPlayer.play(2);delay(1000);digitalWrite(RELE,HIGH);}
    int clock_seg = clock_update();
    if(clock_seg == 0){
     // myDFPlayer.play(3);
    }
    if(clock_seg == ((MINUTOS-TIEMPO_VAMPIRO)*60) ){digitalWrite(UNL2,HIGH);}
  }
}
void if_resuelto()
{
  if(resuelto){
    
  }
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
  //  Serial.println(check(0,RS,DS));
    timer_print = millis();
    
    }
  }

int clock_update()
{
      if(tiempo_restante == 0){return -1;}
      if ((millis() - contador_tiempo) >= 1000) {        //
      contador_tiempo = millis();
      if(tiempo_restante != 0){
        tiempo_restante = tiempo_restante - 1;
        int dimmer = map(tiempo_restante,0,MINUTOS*60,0,255);
        analogWrite(UNL1, dimmer);
      }
    }
  return tiempo_restante;
}

//NO EDITABLE
//comprueba el estado de un sensor
boolean check (boolean cual, int entrada, int ds)
{
  boolean resu = false;
  int contador = 0;  
  if(cual){ while(digitalRead(entrada) == 1 && resu == false){/*delay(ds);*/contador++;if(contador == ds){resu = true;}}
  }else{    while(digitalRead(entrada) == 0 && resu == false){/*delay(ds);*/contador++;if(contador == ds){resu = true;}}}  
  return resu; 
}
