/* Base Sputnik Slave
 *  
 *  
 *  
 *  
 *  
 * 3/02/2020 
 */

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//DEFINES
#define SPRINT      true
#define NEED_REPOSO true

#define NLED        4

#define A           2
#define TX          3
#define OUT         4
#define R           7
#define A           2
#define M1          9
#define M2          5
#define M3          6
//#define R1          A0
//#define R2          A1

#define B0T1           8
#define B0T2           10


#define NCOLORES    6

#define DS  200

#define TIEMPO_LETRA    1000

//CONSTANTES
const int N_INPUTS = 4;
const int INPUTS[N_INPUTS] = {R , A, B0T1,B0T2};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1,1};
const int N_OUTPUTS = 3;
const int OUTPUTS[N_OUTPUTS] = {M1,M2,OUT};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,0,0};


//VARIABLES
unsigned long contador_tiempo = 0;
const int NR = 8;
const int RESPUESTA[NR] = {1,1,1,0,0,1,0,0};
unsigned long luzcount = 0;

int correcta = 0;

int apriete = -1;

//NO EDITABLE
boolean reposo = false;
boolean activo = false;
boolean resuelto = false;
unsigned long timer_print = 0;
unsigned long contadoraudio = 0;

SoftwareSerial mySoftwareSerial(500, 3);    // RX, TX
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
    mySoftwareSerial.begin(9600);
  Serial.println("INICIANDO");
  if (!myDFPlayer.begin(mySoftwareSerial)) {                     //Arranca dfplayer
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    Serial.println(myDFPlayer.readState()); //read mp3 state
    Serial.println(myDFPlayer.readFileCounts()); //read all file counts in SD card
  }
  myDFPlayer.volume(10);
//si necesita reposo
  if(NEED_REPOSO){reposo=true;activo=false;resuelto=false;}else{reposo=false;activo=true;resuelto=false;}
//EDITABLE
 myDFPlayer.volume(15);
 myDFPlayer.play(1);
}

///////////////////////////////////////LOOP//////////////////////////////////////////
void loop() {
  if_reposo();
  if_activo();
  if_resuelto();
  showme();
  if(millis() - contadoraudio > 2683000){
    contadoraudio = millis();
    myDFPlayer.play(1);
    
    }
}

////////////////////////////////////////FUNCIONES///////////////////////////////////
//EDITABLE
void if_reposo()
{
  if(reposo){
    if(check(0, R, DS)){reposo = false; activo = true;}
  }
}

void if_activo()
{
  if(activo){
    int bact = -1;
    for(int i = 0;i < 2 ; i++){
      if(check(0, INPUTS[i+2],DS)){bact = i;
      i = 2;
      digitalWrite(M2,HIGH);
      luzcount = millis();  
      }}
    if(millis() - luzcount > 1000){digitalWrite(M2, LOW);}

      if(bact > -1 && apriete != bact ){
        apriete = bact;      
        Serial.print("Boton: "); Serial.println(bact); 
        Serial.print("secuencia: "); Serial.println(correcta);
        if(bact == RESPUESTA[correcta]){correcta++;}else{correcta = 0;}

      }

      if(correcta == NR || check(0, A, DS)){reposo = false; activo = false; resuelto = true;}   

      if(check(1, INPUTS[2],DS) && check(1, INPUTS[1+2],DS)){apriete = -1;}



  }
}

void if_resuelto()
{
  if(resuelto){
    digitalWrite(M1, LOW);
    digitalWrite(OUT, HIGH);
    if(check(1, R, DS) && check(0, A, DS)){reset();}
  }
}

void reset(){
  
    if(NEED_REPOSO){reposo=true;activo=false;resuelto=false;}else{reposo=false;activo=true;resuelto=false;}
  //declara entradas
  for(int a = 0;a < N_INPUTS;a++){ 
    pinMode(INPUTS[a] , INPUT);
    digitalWrite(INPUTS[a] , INPUTS_ISTATE[a]);
  }
//declara salidas
  for(int a = 0;a < N_OUTPUTS;a++){ 
    pinMode(OUTPUTS[a] , OUTPUT);
    digitalWrite(OUTPUTS[a] , OUTPUTS_ISTATE[a]);}

    correcta = 0;
    apriete = -1;
  }

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");

    timer_print = millis();
    
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
