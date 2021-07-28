/* Ataud Ouija
 * 
 * Arduino NANO, UN RS, 2 RELES, dos palancas
 * 
 * Siempre andando, al cerrar RS libera un rele,despues detecta un sensor de audio por 10 seg y si dura abre puerta final
 * 
 * Sputnik 30/5/19
 */

//INCLUDES
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h" 

//DEFINES
#define SPRINT      true
#define NEED_REPOSO true
#define PAL1        2
#define PAL2        3
#define RED1        6
#define REL1        4
#define REL2        5
#define REL3        7
#define REL4        11

#define DS  200
#define DELAY_HABLA  500
#define DELAY_FIN    1500

//CONSTANTES
const int N_INPUTS = 3;
const int INPUTS[N_INPUTS] = {RED1,PAL1,PAL2};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1};
const int N_OUTPUTS = 4;
const int OUTPUTS[N_OUTPUTS] = {REL1,REL2,REL3,REL4};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,1,0,1};


//VARIABLES
unsigned long contador_tiempo = 0;
unsigned long timer_letra = 0;

//OBJETOS

//NO EDITABLE
boolean reposo = false;
boolean activo = false;
boolean resuelto = false;
unsigned long timer_print = 0;

SoftwareSerial mySoftwareSerial(11, 12);    // RX, TX
DFRobotDFPlayerMini myDFPlayer; 
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
  delay(1000);
  if (!myDFPlayer.begin(mySoftwareSerial)) {}
  myDFPlayer.volume(30);
  myDFPlayer.loop(1);
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
    if(check(0,PAL1,DS) || check(0,RED1,DS)){activo = true;reposo = false;digitalWrite(REL1,LOW);}
  }
}

void if_activo()
{
  if(activo){
//    boolean ganaron = false;
//    int sensorValue = analogRead(A0);
//    if(sensorValue < 500){contador_tiempo = millis();}
//    if((millis()-contador_tiempo) < DELAY_HABLA){}else{timer_letra = millis();}
//    if((millis()-timer_letra) > DELAY_FIN){ganaron = true;}
//    if(check(0,PAL2,DS) || ganaron){digitalWrite(REL3,HIGH);digitalWrite(REL4,LOW);delay(5000);activo = false; resuelto = true;digitalWrite(REL4,HIGH);}

  }
}

void if_resuelto()
{
  if(resuelto){
     digitalWrite(REL2,LOW);
  }
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    Serial.print("pal1 ");Serial.println(digitalRead(PAL1));
    Serial.print("pal2 ");Serial.println(digitalRead(PAL2));
    Serial.print("AO ");Serial.println(analogRead(A0));
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


