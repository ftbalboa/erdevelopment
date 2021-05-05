/* PANEL_04_05
 * 
 * MEGA, DFPLAYER, BOTONES, LUCES Y RELE
 * 
 */
 
//INCLUDES
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
 
//EDITABLE
#define SPRINT      false
#define NEED_REPOSO true
#define POTES    22
#define PALAN    23
#define LUCES    24
#define MEDAL    25
#define VUEL1    26
#define VUEL2    28
#define VUEL3    27
#define LEDPO    29
#define LEDPA    30
#define LEDLU    31
#define LEDME    32
#define INPAL    33
#define OUTPA    34
#define ALERT    35
#define RX        2
#define TX        3
#define RELE1    36
#define RELE2    37
#define DS       5

#define IZQ       1
#define DER       2

const int N_INPUTS = 8;
const int INPUTS[N_INPUTS] = {POTES,PALAN,LUCES,MEDAL,VUEL1,VUEL2,VUEL3,INPAL};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1,1,1,1,1,1};
const int N_OUTPUTS = 8;
const int OUTPUTS[N_OUTPUTS] = {RELE1,RELE2,LEDPO,LEDPA,LEDLU,LEDME,ALERT,OUTPA};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,1,0,0,0,0,0,1};

unsigned long timer_alert = 0;
int contador_audio = 0;
boolean blin = false;
int referencia = -1;
int retencion = -1;
int estado_vuelta = 0;
boolean izquierda = false;
boolean derecha = false;
const int LARGO_SECUENCIA = 7;
int SECUENCIA[LARGO_SECUENCIA]{IZQ,IZQ,DER,DER,IZQ,IZQ,IZQ};
int posicion = 0;
unsigned long timer_led = 0;

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
    boolean timmeron = false;
    boolean potesok = false;
    boolean palanok = false;
    boolean lucesok = false;
    boolean medalok = false;
    if(check(0, POTES ,DS)){digitalWrite(LEDPO , HIGH);potesok = true;}else{digitalWrite(LEDPO , LOW);}
    if(check(1, PALAN ,DS)){digitalWrite(LEDPA , HIGH);palanok = true;}else{digitalWrite(LEDPA , LOW);}
    if(check(0, LUCES ,DS)){digitalWrite(LEDLU , HIGH);lucesok = true;}else{digitalWrite(LEDLU , LOW);}
    if(check(0, MEDAL ,DS)){digitalWrite(LEDME , HIGH);medalok = true;}else{digitalWrite(LEDME , LOW);}
    if(potesok && palanok && lucesok && medalok || check(0,INPAL,DS)){timmeron = true;}
    if(timmeron){
      contador_audio++;
      if(contador_audio == 20){
        activo= true; 
        reposo = false;
        myDFPlayer.loop(2);
        digitalWrite(RELE2,LOW);
        digitalWrite(LEDPO , LOW);
        digitalWrite(LEDPA , LOW);
        digitalWrite(LEDLU , LOW);
        digitalWrite(LEDME , LOW);digitalWrite(ALERT , LOW);
        digitalWrite(OUTPA , LOW);myDFPlayer.loop(2);}
    }else{contador_audio = 0;}
  }
}

void if_activo()
{
  if(activo){
    int vue = 0;digitalWrite(RELE2,LOW);digitalWrite(RELE1,HIGH);
    if(millis()-timer_alert > 500){if(blin){digitalWrite(ALERT,HIGH);blin=false;}else{digitalWrite(ALERT,LOW);blin=true;}timer_alert=millis();}
    if(check(0, VUEL1 ,DS)){if(retencion != 1){if(referencia == -1){referencia = 1;}else{vue=vuelteando(referencia, retencion, 1);}retencion=1;}}
    if(check(0, VUEL2 ,DS)){if(retencion != 2){if(referencia == -1){referencia = 2;}else{vue=vuelteando(referencia, retencion, 2);}retencion=2;}}
    if(check(0, VUEL3 ,DS)){if(retencion != 3){if(referencia == -1){referencia = 3;}else{vue=vuelteando(referencia, retencion, 3);}retencion=3;}}
    if(vue == 1){
      timer_led = millis();
      if(vue == SECUENCIA[posicion]){
        digitalWrite(LEDPO , HIGH);
        digitalWrite(LEDPA , HIGH);
        digitalWrite(LEDLU , LOW);
        digitalWrite(LEDME , LOW);
        posicion++;}
        else{
        digitalWrite(LEDPO , HIGH);
        digitalWrite(LEDPA , HIGH);
        digitalWrite(LEDLU , HIGH);
        digitalWrite(LEDME , HIGH);
        posicion = 0;  
          }}
    if(vue == 2){
      timer_led = millis();
      if(vue == SECUENCIA[posicion]){
        digitalWrite(LEDPO , LOW);
        digitalWrite(LEDPA , LOW);
        digitalWrite(LEDLU , HIGH);
        digitalWrite(LEDME , HIGH);
        posicion++;}
        else{
        digitalWrite(LEDPO , HIGH);
        digitalWrite(LEDPA , HIGH);
        digitalWrite(LEDLU , HIGH);
        digitalWrite(LEDME , HIGH);
        posicion = 0;  
          }}
    if(millis() - timer_led > 1000){
      digitalWrite(LEDPO , LOW);
      digitalWrite(LEDPA , LOW);
      digitalWrite(LEDLU , LOW);
      digitalWrite(LEDME , LOW);
      }
    if(posicion == LARGO_SECUENCIA){
        myDFPlayer.loop(1);
        activo=false;
        resuelto=true;        
        digitalWrite(LEDPO , HIGH);
        digitalWrite(LEDPA , HIGH);
        digitalWrite(LEDLU , HIGH);
        digitalWrite(LEDME , HIGH);}
  }
}

void if_resuelto()
{
  if(resuelto){
    digitalWrite(ALERT , LOW);
    digitalWrite(RELE2,HIGH);
    digitalWrite(RELE1,LOW);
  }
}

int vuelteando (int ref, int ant, int act)    // 0 nada, 1 izquierda, 2 derecha
{
  switch(ref){
    
    case 1:
      switch(act){
        case 1:
          if (estado_vuelta == 2){estado_vuelta = 0; return 1;}else{
            if (estado_vuelta == -2){estado_vuelta = 0; return 2;}else{
            referencia = ant;
            retencion = 1;
            if (referencia == 2){estado_vuelta = 1;}else{estado_vuelta = -1;}}}
        break;
        case 2:
          if(estado_vuelta == 0){estado_vuelta = -1;}
          if(estado_vuelta == 1){estado_vuelta = 2;}
        break;
        case 3:
          if(estado_vuelta == -1){estado_vuelta = -2;}else{if(estado_vuelta == 0){estado_vuelta = 1;}}
        break;
        }
    break;

    case 2:
      switch(act){
        case 1:
          if(estado_vuelta == -1){estado_vuelta = -2;}else{if(estado_vuelta == 0){estado_vuelta = 1;}}
        break;
        case 2:
          if (estado_vuelta == 2){estado_vuelta = 0; return 1;}else{
            if (estado_vuelta == -2){estado_vuelta = 0; return 2;}else{
            referencia = ant;
            retencion = 2;
            if (referencia == 1){estado_vuelta = -1;}else{estado_vuelta = 1;}}}
        break;
        case 3:
          if(estado_vuelta == 0){estado_vuelta = -1;}
          if(estado_vuelta == 1){estado_vuelta = 2;}
        break;
        }    
    break;

    case 3:
      switch(act){
        case 1:
          if(estado_vuelta == 0){estado_vuelta = -1;}
          if(estado_vuelta == 1){estado_vuelta = 2;}
        break;
        case 2:
          if(estado_vuelta == -1){estado_vuelta = -2;}else{if(estado_vuelta == 0){estado_vuelta = 1;}}
        break;
        case 3:
          if (estado_vuelta == 2){estado_vuelta = 0; return 1;}else{
            if (estado_vuelta == -2){estado_vuelta = 0; return 2;}else{
            referencia = ant;
            retencion = 3;
            if (referencia == 2){estado_vuelta = -1;}else{estado_vuelta = 1;}}}
        break;
        }    
    break;
    
    }
    return 0;
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    Serial.print("lugar: ");
    Serial.println(posicion);
    Serial.print("retencion: ");
    Serial.println(retencion);
    Serial.print("referencia: ");
    Serial.println(referencia);
    Serial.print("vuelta: ");
    Serial.println(estado_vuelta);
    Serial.print("state: ");
    Serial.print(check(1, VUEL1 ,DS));
    Serial.print(check(1, VUEL2 ,DS));
    Serial.println(check(1, VUEL3 ,DS));
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
