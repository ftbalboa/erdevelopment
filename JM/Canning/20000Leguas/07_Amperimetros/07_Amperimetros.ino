/* AMPERIMETROS_07
 * 
 * MEGA, DFPLAYER, BOTONES, AMPERIMETROS Y RELE
 * 
 */
 
//INCLUDES
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
 
//EDITABLE
#define SPRINT      false
#define NEED_REPOSO false
#define RELE  29
#define AMP1  8
#define AMP2  9
#define AMP3  10
#define B1    23
#define B2    22
#define B3    25
#define B4    24
#define B5    27
#define B6    26
#define RX    2
#define TX    3
#define DS    30

#define RES_AMP1 230
#define RES_AMP2 50
#define RES_AMP3 170
#define CHANGUI 20
#define LIM_AMP1 255
#define LIM_AMP2 255
#define LIM_AMP3 210

#define VELOCIDAD 10

const int N_INPUTS = 6;
const int INPUTS[N_INPUTS] = {B1,B2,B3,B4,B5,B6};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1,1,1,1};
const int N_OUTPUTS = 2;
const int OUTPUTS[N_OUTPUTS] = {28,RELE};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,1};


int lug_amp1 = 0;
int lug_amp2 = 0;
int lug_amp3 = 0;

unsigned long contador_audio = 0;


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
  pinMode(AMP1 , OUTPUT);
  pinMode(AMP2 , OUTPUT);
  pinMode(AMP3 , OUTPUT);
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
    boolean timmeron = false;
    boolean amp1ok = false;
    boolean amp2ok = false;
    boolean amp3ok = false;
    if(check(0, B1 ,DS)){if(lug_amp1 < LIM_AMP1-VELOCIDAD){lug_amp1=lug_amp1+VELOCIDAD;analogWrite(AMP1 , lug_amp1);}}
    if(check(0, B2 ,DS)){if(lug_amp1 > 0+VELOCIDAD){lug_amp1=lug_amp1-VELOCIDAD;analogWrite(AMP1 , lug_amp1);}}
    if(check(0, B3 ,DS)){if(lug_amp2 < LIM_AMP2-VELOCIDAD){lug_amp2=lug_amp2+VELOCIDAD;analogWrite(AMP2 , lug_amp2);}}
    if(check(0, B4 ,DS)){if(lug_amp2 > 0+VELOCIDAD){lug_amp2=lug_amp2-VELOCIDAD;analogWrite(AMP2 , lug_amp2);}}
    if(check(0, B5 ,DS)){if(lug_amp3 < LIM_AMP3-VELOCIDAD){lug_amp3=lug_amp3+VELOCIDAD;analogWrite(AMP3 , lug_amp3);}}
    if(check(0, B6 ,DS)){if(lug_amp3 > 0+VELOCIDAD){lug_amp3=lug_amp3-VELOCIDAD;analogWrite(AMP3 , lug_amp3);}}
    if(lug_amp1>RES_AMP1-CHANGUI && lug_amp1<RES_AMP1+CHANGUI){amp1ok = true;}
    if(lug_amp2>RES_AMP2-CHANGUI && lug_amp2<RES_AMP2+CHANGUI){amp2ok = true;}
    if(lug_amp3>RES_AMP3-CHANGUI && lug_amp3<RES_AMP3+CHANGUI){amp3ok = true;}
    if(amp1ok && amp2ok && amp3ok){timmeron = true;}
    if(timmeron){contador_audio++;if(contador_audio == 120000){activo= false; resuelto = true;myDFPlayer.play(1);}}else{contador_audio = 0;}
  }
}

void if_resuelto()
{
  if(resuelto){
    digitalWrite(RELE, LOW);
  }
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    Serial.print("AMP1: ");
    Serial.println(lug_amp1);
    Serial.print("AMP2: ");
    Serial.println(lug_amp2);
    Serial.print("AMP3: ");
    Serial.println(lug_amp3);
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
