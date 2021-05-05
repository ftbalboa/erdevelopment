/* Caja audio Pablo Escobar
 *  
 * Arduino Nano,8 botones NA, DFPLAYER y 1 LED
 * 
 * Al apretar alguno de los ocho botones reproduce 
 * audio correspondiente y enciende led durante la
 * reproduccion
 * 
 * Sputnik 22/5/19
 */

//INCLUDES
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h" 
 
//EDITABLE
#define SPRINT      true
#define DFTX        10
#define DFRX        11
#define BOT0        9
#define BOT1        8
#define BOT2        7
#define BOT3        6
#define BOT4        5
#define BOT5        4
#define BOT6        3
#define BOT7        2
#define LED0        12

#define DS  20

const int N_INPUTS = 8;
const int INPUTS[N_INPUTS] = {BOT0,BOT1,BOT2,BOT3,BOT4,BOT5,BOT6,BOT7};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1,1,1,1,1,1};
const int N_OUTPUTS = 1;
const int OUTPUTS[N_OUTPUTS] = {LED0};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {0};

const int TRACK_TIME[8] = {34,34,38,30,8,25,11,14};

SoftwareSerial mySoftwareSerial(DFRX, DFTX);    // RX, TX
DFRobotDFPlayerMini myDFPlayer; 

boolean sensores_act[N_INPUTS]{false,false,false,false,false,false,false,false};

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
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial)) {}
  //myDFPlayer.play(1);
  digitalWrite(LED0, HIGH);
  delay(1000);
  digitalWrite(LED0,LOW);
}

///////////////////////////////////////LOOP//////////////////////////////////////////
void loop() {
  sensorea();
  for(int a = 0 ; a < N_INPUTS ; a++){
    if( sensores_act[a]){
      digitalWrite(LED0, HIGH);
      myDFPlayer.play(a+1);
      pierde_tiempo(TRACK_TIME[a] * 1000);
      digitalWrite(LED0, LOW);
      }
  }
  showme();
}

////////////////////////////////////////FUNCIONES///////////////////////////////////
//EDITABLE


void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    for(int a = 0 ; a < N_INPUTS ; a++){
      Serial.print(sensores_act[a]);
    }
    Serial.println("");
    timer_print = millis();
    
    }
  }

void sensorea ()
{
  for(int a = 0 ; a < N_INPUTS ; a++){
  sensores_act[a] = check(0 , INPUTS[a] , DS);
  }
}

void pierde_tiempo (unsigned int tiempo)
{
  unsigned long perdiendo = millis();
  while(millis() - perdiendo < tiempo){}
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
