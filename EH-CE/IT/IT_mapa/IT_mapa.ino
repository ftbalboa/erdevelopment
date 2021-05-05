/* PIANO_06
 * 
 * MEGA, SENSORES DE RANURA Y RELE
 * 
 */

//INCLUDES
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
 
//EDITABLE
#define SPRINT true
#define NEED_REPOSO false
#define RELE  A0
#define C1    2
#define CS    8
#define D1    10
#define E1    11
#define F1    12
#define G1    15
#define A1    A2
#define B1    A3
#define C2    A4
#define C3    A5

#define DS    5000
const int N_INPUTS = 10;
const int INPUTS[N_INPUTS] = {C1,CS,D1,E1,F1,G1,A1,B1,C2,C3};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1,1,1,1,1,1,1,1};
const int N_OUTPUTS = 1;
const int OUTPUTS[N_OUTPUTS] = {RELE};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {0};

const int LARGO_SECUENCIA = /*16*/10;
const int SECUENCIA[LARGO_SECUENCIA]={C1,A1,C2,G1,D1,B1,F1,C3,CS,E1};

int lugar = 0;

boolean ret_C1 = false;
boolean ret_CS = false;
boolean ret_D1 = false;
boolean ret_E1 = false;
boolean ret_F1 = false;
boolean ret_G1 = false;
boolean ret_A1 = false;
boolean ret_B1 = false;
boolean ret_C2 = false;
boolean ret_C3 = false;

//NO EDITABLE
boolean reposo = false;
boolean activo = false;
boolean resuelto = false;
unsigned long timer_print = 0;

//OBJETOS
SoftwareSerial mySoftwareSerial(99, 3);    // RX, TX
DFRobotDFPlayerMini myDFPlayer;                     //dfplayer
void printDetail(uint8_t type, int value);          //dfplayer

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
  if (!myDFPlayer.begin(mySoftwareSerial)) {                     //Arranca dfplayer
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    Serial.println(myDFPlayer.readState()); //read mp3 state
    Serial.println(myDFPlayer.readFileCounts()); //read all file counts in SD card
  }

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

    if(check(0, C1 ,DS)){
      if(ret_C1){}else{myDFPlayer.play(1);ret_C1=true; if(C1 == SECUENCIA[lugar]){lugar++;}else{lugar = 0;}}
    }else{
      ret_C1=false;}
    if(lugar == LARGO_SECUENCIA){lugar = 0; activo = false; resuelto = true;}
    if(check(0, CS ,DS)){
      if(ret_CS){}else{myDFPlayer.play(1);ret_CS=true; if(CS == SECUENCIA[lugar]){lugar++;}else{lugar = 0;}}
    }else{
      ret_CS=false;}
    if(lugar == LARGO_SECUENCIA){lugar = 0; activo = false; resuelto = true;}
    if(check(0, D1 ,DS)){
      if(ret_D1){}else{myDFPlayer.play(1);ret_D1=true; if(D1 == SECUENCIA[lugar]){lugar++;}else{lugar = 0;}}
    }else{
      ret_D1=false;}
    if(lugar == LARGO_SECUENCIA){lugar = 0; activo = false; resuelto = true;}
    if(check(0, E1 ,DS)){
      if(ret_E1){}else{myDFPlayer.play(1);ret_E1=true; if(E1 == SECUENCIA[lugar]){lugar++;}else{lugar = 0;}}
    }else{
      ret_E1=false;}
    if(lugar == LARGO_SECUENCIA){lugar = 0; activo = false; resuelto = true;}
    if(check(0, F1 ,DS)){
      if(ret_F1){}else{myDFPlayer.play(1);ret_F1=true; if(F1 == SECUENCIA[lugar]){lugar++;}else{lugar = 0;}}
    }else{
      ret_F1=false;}
    if(lugar == LARGO_SECUENCIA){lugar = 0; activo = false; resuelto = true;}
    if(check(0, G1 ,DS)){
      if(ret_G1){}else{myDFPlayer.play(1);ret_G1=true; if(G1 == SECUENCIA[lugar]){lugar++;}else{lugar = 0;}}
    }else{
      ret_G1=false;}
    if(lugar == LARGO_SECUENCIA){lugar = 0; activo = false; resuelto = true;}
    if(check(0, A1 ,DS)){
      if(ret_A1){}else{myDFPlayer.play(1);ret_A1=true; if(A1 == SECUENCIA[lugar]){lugar++;}else{lugar = 0;}}
    }else{
      ret_A1=false;}
   if(lugar == LARGO_SECUENCIA){lugar = 0; activo = false; resuelto = true;}   
   if(check(0, B1 ,DS)){
      if(ret_B1){}else{myDFPlayer.play(1);ret_B1=true; if(B1 == SECUENCIA[lugar]){lugar++;}else{lugar = 0;}}
    }else{
      ret_B1=false;}
   if(lugar == LARGO_SECUENCIA){lugar = 0; activo = false; resuelto = true;}
   if(check(0, C2 ,DS)){
      if(ret_C2){}else{myDFPlayer.play(1);ret_C2=true; if(C2 == SECUENCIA[lugar]){lugar++;}else{lugar = 0;}}
    }else{
      ret_C2=false;}
   if(lugar == LARGO_SECUENCIA){lugar = 0; activo = false; resuelto = true;} 
   if(check(0, C3 ,DS)){
      if(ret_C3){}else{myDFPlayer.play(1);ret_C3=true; if(C3 == SECUENCIA[lugar]){lugar++;}else{lugar = 0;}}
    }else{
      ret_C3=false;}
   if(lugar == LARGO_SECUENCIA){lugar = 0; activo = false; resuelto = true;} 
    delay(100);
  }
}

void if_resuelto()
{
  if(resuelto){
    myDFPlayer.play(2);
    digitalWrite(RELE, 1);
    delay(30000);
    digitalWrite(RELE, 0);    
    lugar =0;
    resuelto = false;
    activo = true;
  }
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");timer_print = millis();
    Serial.print("C1: ");
    Serial.println(ret_C1);
    Serial.print("CS: ");
    Serial.println(ret_CS);
    Serial.print("D1: ");
    Serial.println(ret_D1);
    Serial.print("E1: ");
    Serial.println(ret_E1);
    Serial.print("F1: ");
    Serial.println(ret_F1);
    Serial.print("G1: ");
    Serial.println(ret_G1);
    Serial.print("A1: ");
    Serial.println(ret_A1);
    Serial.print("B1: ");
    Serial.println(ret_B1);
    Serial.print("C2: ");
    Serial.println(ret_C2);
    Serial.print("C3: ");
    Serial.println(ret_C3);
    Serial.print("Lugar: ");
    Serial.println(lugar);
    }
  }

//NO EDITABLE
//comprueba el estado de un sensor
boolean check (boolean cual, int entrada, int ds)
{
  boolean resu = false;
  int contador = 0;  
  if(cual){ while(digitalRead(entrada) == 1 && resu == false){/*delay(ds);*/contador++;if(contador == DS){resu = true;}}
  }else{    while(digitalRead(entrada) == 0 && resu == false){/*delay(ds);*/contador++;if(contador == DS){resu = true;}}}  
  return resu; 
}
