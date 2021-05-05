/* VELAS_01
 * 
 * MEGA, DFPLAYER, S.VENTANA, VELAS Y RELE
 * 
 */
 
//INCLUDES
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
 
//EDITABLE
#define SPRINT      false
#define NEED_REPOSO false
#define SVENT    22
#define RX        2
#define TX        3
#define RELE1    24
#define RELE2    23
#define DS       10

const int N_INPUTS = 1;
const int INPUTS[N_INPUTS] = {SVENT};
const int INPUTS_ISTATE[N_INPUTS] = {1};
const int N_OUTPUTS = 2;
const int OUTPUTS[N_OUTPUTS] = {RELE1,RELE2};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,0};

//OBJETOS
SoftwareSerial mySoftwareSerial(RX, TX);    // RX, TX
DFRobotDFPlayerMini myDFPlayer;                     //dfplayer
void printDetail(uint8_t type, int value);          //dfplayer

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
  if (!myDFPlayer.begin(mySoftwareSerial)) {                     //Arranca dfplayer
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    Serial.println(myDFPlayer.readState()); //read mp3 state
    Serial.println(myDFPlayer.readFileCounts()); //read all file counts in SD card
  }
  myDFPlayer.volume(30);
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
    if(check(0,SVENT,DS)){if(check(0,SVENT,DS)){activo = false; resuelto = true;  myDFPlayer.play(1);}}
    
    }

}

void if_resuelto()
{
  if(resuelto){
    digitalWrite(RELE2,HIGH);
    digitalWrite(RELE1,LOW);
  }
}


void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    Serial.print("SVENT: ");
    Serial.println(check(0,SVENT,DS));
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
