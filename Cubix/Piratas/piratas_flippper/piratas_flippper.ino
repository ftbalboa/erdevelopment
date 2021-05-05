/* Flipper BarcoPirata
 * 
 * Arduino NANO,  1 RS, 1 RELES, 2 MOSSFFET
 * 1 DFPLAYER, 3 LEDSL, 1 SENSOR DE OBSTACULO
 * 
 * reinicia con iman en 0 20 segundos
 * 
 * Sputnik 11/12/20
 */

 //INCLUDES
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//DEFINES
#define SPRINT      true
#define NEED_REPOSO true

#define BOLA        2
#define HTCBOLA     false

#define LED1        3
#define LED2        4
#define LED3        5

#define TX_ADF     10
#define RX_ADF     11

#define MOS1        7
#define MOS2        8

#define RELE        9

#define IMAN        12

#define DS  200
#define SEGURO_BOLA  5000

#define TIEMPO_RESET 20000
#define TIEMPO_PARPADEO 100
//CONSTANTES
const int N_INPUTS = 2;
const int INPUTS[N_INPUTS] = {BOLA, IMAN};
const int INPUTS_ISTATE[N_INPUTS] = {0,1};
const int N_OUTPUTS = 6;
const int OUTPUTS[N_OUTPUTS] = {LED1,LED2,LED3,RELE,MOS1,MOS2};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {0,0,0,1,0,0};


//VARIABLES
unsigned long contador_tiempo = 0;
unsigned long contador_bola   = 0;
unsigned long contador_reset   = 0;
unsigned long contador_parp = 0;
int score = 0;
int LED[3] = {LED1,LED2,LED3};


//OBJETOS

SoftwareSerial mySoftwareSerial(RX_ADF, TX_ADF);    // RX, TX
DFRobotDFPlayerMini myDFPlayer;                     //dfplayer
void printDetail(uint8_t type, int value);          //dfplayer

//NO EDITABLE
boolean reposo = false;
boolean activo = true;
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
  mySoftwareSerial.begin(9600);
  Serial.println("INICIANDO");
  if (!myDFPlayer.begin(mySoftwareSerial)) {                     //Arranca dfplayer
    Serial.println(F("Unable to begin:"));
  }
  myDFPlayer.volume(20);
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
    digitalWrite(RELE,HIGH);
    digitalWrite(LED[0],false);
    digitalWrite(LED[1],false);
    digitalWrite(LED[2],false);
    digitalWrite(MOS1,false);
    digitalWrite(MOS2,false);
    score = 0;
    if(check(1, IMAN, DS)){
      reposo = false;
      activo = true;
      myDFPlayer.play(1);      
      }
  }
}

void if_activo()
{
  if(activo){
    parpadea();
    resetea();
    if(millis() - contador_bola > SEGURO_BOLA){
      if(check(HTCBOLA,BOLA,DS)){
        digitalWrite(MOS1,true);
        digitalWrite(MOS2,false);
        myDFPlayer.play(2); 
        score++;
        delay(5000);
        digitalWrite(MOS1,false);
        contador_bola = millis();
        myDFPlayer.play(1); 
        digitalWrite(LED[score-1],true);
        }
        if(score == 3){
          resuelto = true;
          activo = false; 
          }
    }

  }
}


void if_resuelto()
{
  if(resuelto){
    resetea();
    digitalWrite(RELE,LOW);
    digitalWrite(MOS1,false);
    digitalWrite(MOS2,false);
  }
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    for(int i = 0;i<N_INPUTS;i++){
      Serial.println(digitalRead(INPUTS[i]));}
    Serial.print("score: ");
    Serial.println(score);
    timer_print = millis();
    
    }
  }

void resetea(){
    boolean correr = true;
    unsigned long contador_reset = millis();
    while(check(0, IMAN, DS) && correr){
      if(millis() - contador_reset > TIEMPO_RESET){
      reposo = true;
      resuelto = false;
      activo = false;
      myDFPlayer.play(2);  
      correr = false;    
      }   
  }
}

void parpadea(){
  if(millis() - contador_parp > TIEMPO_PARPADEO){
    int def = random(0,3);
    if(def == 1){ digitalWrite(MOS2,0);}else{digitalWrite(MOS2,1);}
    contador_parp = millis();
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

