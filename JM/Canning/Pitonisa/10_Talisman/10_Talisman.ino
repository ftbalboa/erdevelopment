/* DIOSES_09
 * 
 * MEGA,RFID SERIAL Y RELE
 * 
 */
 
//INCLUDES
#include "SoftwareSerial.h"
#include "rdm630.h"
 
//EDITABLE
#define SPRINT      true
#define NEED_REPOSO false
#define RX        2
#define TX        3
#define RELE1    22
#define RELE2    23
#define OPTO     24
#define PUNAL    25
#define TALI     30
#define DS       10

const int N_INPUTS = 2;
const int INPUTS[N_INPUTS] = {PUNAL,TALI};
const int INPUTS_ISTATE[N_INPUTS] = {1,0};
const int N_OUTPUTS = 3;
const int OUTPUTS[N_OUTPUTS] = {RELE1,RELE2, OPTO};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,1,0};

const int SENSORES = 1;

char RESPUESTA1[14]={'0','2','5','0','0','C','0','B','D','E','2','B','A'};//02500C0BDE2BA




char tag1[14];


boolean actual[] = {false,false};

char tagNumber[14];

String tagString;

String RESPUESTA = "02500C0BDE2BA";

boolean video = true;

//NO EDITABLE
boolean reposo = false;
boolean activo = false;
boolean resuelto = false;
unsigned long timer_print = 0;
////////////////////////////////////SETUP///////////////////////////////
//NO EDITABLE
void setup() {
  delay(5000);
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

    int resu = 0;

    if(check(1,TALI,DS)){digitalWrite(OPTO,HIGH); delay(5000);   digitalWrite(OPTO,LOW);delay(5000);activo=false;resuelto=true;}else{resu = 0;}

    if(video && check(0,PUNAL,DS)){digitalWrite(RELE2 , LOW); delay(5000); digitalWrite(RELE2 , HIGH); video = false;}
    
    }

}

void if_resuelto()
{
  if(resuelto){
    digitalWrite(RELE1,LOW);
  }
}



void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
      Serial.print("TAG ");
      Serial.print('1');
      Serial.print(" :");
      Serial.println(check(1,TALI,DS));
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
