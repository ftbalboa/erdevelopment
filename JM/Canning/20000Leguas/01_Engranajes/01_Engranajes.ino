/* PANEL_04_05
 * 
 * MEGA, DFPLAYER, BOTONES, LUCES Y RELES
 * 
 */
 
//INCLUDES
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
 
//EDITABLE
#define SPRINT      false
#define NEED_REPOSO false
#define SVENT    22
#define ENGRA    23
#define PALAN    24
#define LUZFI    26
#define LUZPA    25
#define BOTIN    27
#define BOTOU    28

#define DS       30
#define TIEMPO_DELAY 500

#define RX        2
#define TX        3

const int N_INPUTS = 4;
const int INPUTS[N_INPUTS] = {SVENT,ENGRA,PALAN,BOTIN};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1,1};
const int N_OUTPUTS = 3;
const int OUTPUTS[N_OUTPUTS] = {LUZFI, LUZPA, BOTOU};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {0,0,1};


const int LARGO_PARP = 4;
const int LUZ_PARP[LARGO_PARP] = {3,1,4,3};

int lugar = 0;

unsigned long timer_led = 0;
boolean retencion_audio = false;
boolean retencion_botin = false;
boolean engranajes = false;
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
  delay(1000);
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
    boolean cierre = false;
    boolean palanca = false;
    if(check(0, ENGRA ,DS) && !retencion_botin){engranajes = true;}else{}
    if(check(0, SVENT ,DS)){cierre = true;}
    if(check(0, PALAN ,DS)){palanca = true;}
    if(!retencion_botin){if(check(0, BOTIN ,DS)){retencion_botin = true;digitalWrite(BOTOU, LOW);}}
    if((engranajes || retencion_botin) && !cierre){digitalWrite(LUZFI, HIGH);digitalWrite(BOTOU, LOW);}else{digitalWrite(LUZFI, LOW);}
    if(((engranajes && cierre)||retencion_botin) && palanca){digitalWrite(BOTOU, LOW);
      if(retencion_audio){}else{retencion_audio = true;myDFPlayer.play(1);}
    }else{if(retencion_audio){myDFPlayer.pause();}retencion_audio = false;lugar=0;}
    if(retencion_audio){secuencia();}
  }
}

void if_resuelto()
{
  if(resuelto){
  }
}

void secuencia()
{
  if(millis() - timer_led > 999){
  if(lugar < LARGO_PARP){
    int cantidad = LUZ_PARP[lugar];
    for(int a = 0;a < cantidad;a++){digitalWrite(LUZPA, HIGH);delay(TIEMPO_DELAY/2);digitalWrite(LUZPA, LOW);delay(TIEMPO_DELAY/2);}
  }else{}
  lugar++;
  if(lugar == LARGO_PARP + 5){lugar = 0;}
  timer_led=millis();
  }
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    Serial.print("void: ");
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
