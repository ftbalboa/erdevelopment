/* Mesa Ouija
 * 
 * Arduino MEGA, DFPLAYER, AMPLI, UN RS, 4 RELES, UN SERVO, 26 PIXEL, 2 S.CAPACITIVOS ,dos palancas
 * 
 * Siempre andando, al cerrar RS libera un rele(enciende luz), y activa los sensores capacitivos
 * al utilizar los capacitivos se mueve el servo y va creando una secuencia de pixel, al ser correcta
 * activa opto y activa rele, reinicia con power up
 * 
 * Sputnik 30/5/19
 */

//INCLUDES
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h" 
#include <Servo.h>
#include <CapacitiveSensor.h>
#include "FastLED.h"

//DEFINES
#define SPRINT      true
#define NEED_REPOSO true
#define DFTX        2
#define DFRX        3
#define PAL1        22
#define PAL2        23
#define RED1        7
#define PIXE        5
#define OPTO        24
#define REL1        26
#define REL2        27
#define REL3        29
#define REL4        28
#define CAPI        9
#define CAPD        8
#define CAPN        4 
#define SERV        6


#define DS  200

#define MINUTOS     15
#define TIEMPO_LETRA    1000

//CONSTANTES
const int N_INPUTS = 3;
const int INPUTS[N_INPUTS] = {RED1,PAL1,PAL2};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1};
const int N_OUTPUTS = 5;
const int OUTPUTS[N_OUTPUTS] = {REL1,REL2,REL3,REL4,OPTO,};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,1,1,1,0};

const int NFRASE = 8;
const int FRASE[NFRASE] = {0,2,8,13,14,17,4,21};//{0,2,8,13,14,17,4,21};{21,4,17,14,13,8,2,0};

//VARIABLES
unsigned int tiempo_restante = MINUTOS * 60;
unsigned long contador_tiempo = 0;
unsigned long timer_letra = 0;
int serv_pos = 255;
int letra = 0;
int correcta = 0;
boolean activa_letra = false;
int bloquea[NFRASE] = {-1,-1,-1,-1,-1,-1,-1,-1};

//OBJETOS
SoftwareSerial mySoftwareSerial(DFRX, DFTX);    // RX, TX
DFRobotDFPlayerMini myDFPlayer; 
Servo myservo;
CapacitiveSensor   capi = CapacitiveSensor(CAPN,CAPI);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   capd = CapacitiveSensor(CAPN,CAPD); 
CRGB leds[26];

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
  if (!myDFPlayer.begin(mySoftwareSerial)) {}
  myDFPlayer.volume(5);
  myDFPlayer.loop(1);
  myservo.attach(SERV);
  myservo.write(serv_pos); 
  FastLED.addLeds<NEOPIXEL, PIXE>(leds, 26);
  FastLED.setBrightness(  124 );
  FastLED.show();
  capi.set_CS_AutocaL_Millis(0xFFFFFFFF); 
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
  if(reposo){myDFPlayer.volume(5);
    if(check(0,PAL1,DS) || check(0,RED1,DS)){activo = true;reposo = false;digitalWrite(REL3,LOW);delay(5000);digitalWrite(REL3,HIGH);digitalWrite(REL1,LOW);myDFPlayer.loop(2);digitalWrite(REL4,LOW);}
  }
}

void if_activo()
{
  if(activo){
    boolean ouija_ok = false;
    switch(movCap()){
      case 0:{break;}
      case 1: {if(letra < 25){letra++;movete(letra);activa_letra = true;timer_letra = millis();}break;}
      case 2: {if(letra > 0){letra--;movete(letra);activa_letra = true;timer_letra = millis();}break;}
      }
    if(check(0,PAL2,DS) || correcta == NFRASE){ouija_ok = true;}
    if (ouija_ok){
      activo = false;
      resuelto = true;
      digitalWrite(REL1,HIGH);
//      myDFPlayer.loop(3);
      for(int i = 0;i<26;i++){
        color(i,4,0,false);}
      FastLED.show();
      digitalWrite(OPTO,HIGH);
      digitalWrite(REL4,HIGH);
      delay(2000);
      digitalWrite(OPTO,LOW);
      digitalWrite(REL2,LOW);
      myDFPlayer.loop(3);
      delay(20000);
      digitalWrite(REL4,LOW);}
     letreando();
  }
}

void if_resuelto()
{
  if(resuelto){
    
  }
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    Serial.print("pal1 ");Serial.println(digitalRead(PAL1));
    Serial.print("pal2 ");Serial.println(digitalRead(PAL2));
    timer_print = millis();
    
    }
  }

int movCap()
{
 // capi.reset_CS_AutoCal();
  int resu = 0;
  long total1 =  capi.capacitiveSensor(30);    Serial.print("Cap i: ");Serial.print(total1);
  long total2 =  capd.capacitiveSensor(30);    Serial.print("   Cap d: ");Serial.println(total2);
  if(total1 > 2000){resu = 1;}
  if(total2 > 2000){resu = 2;}  
  delay(10);
  return resu;
}

void movete(int letter)
{
      serv_pos = map(letter,0,25,180,0);
      myservo.write(serv_pos); 
      for(int i = 0;i<26;i++){
        if(i == letter){color(i,3,0,false);}
        else{if(i == bloquea[0] || i == bloquea[1] || i == bloquea[2] || i == bloquea[3] || i == bloquea[4] || i == bloquea[5] || i == bloquea[6] || i == bloquea[7] ){color(i,6,0,false);}else{color(i,0,0,false);}}
        }
      FastLED.show();
}

void letreando()
{
  if(millis() - timer_letra > TIEMPO_LETRA && activa_letra)
  {
    activa_letra = false;
    if(FRASE[correcta] == letra){bloquea[correcta] = letra;correcta++;color(letra,6,0,false);}else{correcta=0;color(letra,4,0,false);
    bloquea[0]=-1;
    bloquea[1]=-1;
    bloquea[2]=-1;
    bloquea[3]=-1;
    bloquea[4]=-1;
    bloquea[5]=-1;
    bloquea[6]=-1;
    bloquea[7]=-1;}
    FastLED.show();
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

void color (int led , int col , int tiempo , boolean imprimir) {
  
  switch (col){

    case 0 : 
      leds[led] = CRGB ::Black;
      break;
    
    case 1 :
      leds[led] = CRGB ::Black;
      break;

    case 2 :
      leds[led] = CRGB ::DarkOrange;
      break;

    case 3 :
      leds[led] = CRGB ::White;
      break;

    case 4 :
      leds[led] = CRGB ::Green;
      break;

    case 5 :
      leds[led] = CRGB ::Yellow;
      break;
    
    case 6 :
      leds[led] = CRGB ::Red;
      break;
  
   case 7 :
      leds[led] = CRGB ::Blue;   
      break; 
    }}
