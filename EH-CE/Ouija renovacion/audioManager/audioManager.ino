/* PANEL_04_05
 * 
 * MEGA, DFPLAYER, BOTONES, LUCES Y RELES
 * 
 */
 
//INCLUDES
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
 
//EDITABLE
#define SPRINT      true
#define RELCRUZ  5
#define RELOUIJA 6
#define BOT1     2
#define BOT2     4
#define BOT3     3

#define DS       30
#define TIEMPO_DELAY 500

#define RX        10
#define TX        11

const int N_INPUTS = 3;
const int INPUTS[N_INPUTS] = {BOT1, BOT2, BOT3};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1};
const int N_OUTPUTS = 2;
const int OUTPUTS[N_OUTPUTS] = {RELCRUZ, RELOUIJA};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,1};

boolean bot2Flag = true;
boolean bot3Flag = true;

//OBJETOS
SoftwareSerial mySoftwareSerial(RX, TX);    // RX, TX
DFRobotDFPlayerMini myDFPlayer;                     //dfplayer
void printDetail(uint8_t type, int value);          //dfplayer

//NO EDITABLE
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
  delay(1000);
  myDFPlayer.play(3);
  digitalWrite(RELOUIJA ,0);
  delay(5000);
  digitalWrite(RELOUIJA ,1);
}

///////////////////////////////////////LOOP//////////////////////////////////////////
void loop() {
  if(check(0,BOT1, DS)){myDFPlayer.play(1);}
  if(check(0,BOT2, DS) && bot2Flag){
    bot2Flag = false;
    myDFPlayer.play(2);
    digitalWrite(RELCRUZ ,0);}
  if(check(1,BOT3, DS) && bot3Flag){
    myDFPlayer.play(3);
    bot3Flag = false;
    digitalWrite(RELOUIJA ,0);}
  if(check(1,BOT2, DS) && !bot2Flag){
    bot2Flag = true;
    digitalWrite(RELCRUZ ,1);}
  if(check(0,BOT3, DS) && !bot3Flag){
    bot3Flag = true;
    digitalWrite(RELOUIJA ,1);}
  showme();
}

////////////////////////////////////////FUNCIONES///////////////////////////////////
//EDITABLE

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    Serial.print(check(1,BOT1,DS));
    Serial.print(check(1,BOT2,DS));
    Serial.print(check(1,BOT3,DS));
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
