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
#include <CapacitiveSensor.h>
#include "FastLED.h"

//DEFINES
#define SPRINT      true
#define NEED_REPOSO false
#define RED1        26
#define PIXE        3
#define REL1        12
#define CAPI        A0
#define CAPD        A1
#define CAPNI       5


#define DS  200

#define TIEMPO_LETRA    1000

//CONSTANTES
const int N_OUTPUTS = 5;
const int OUTPUTS[N_OUTPUTS] = {REL1};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1};

const int NFRASE = 7;
const int FRASE[NFRASE] = {8,21,20,17,23,5,14};//{0,2,8,13,14,17,4,21};{21,4,17,14,13,8,2,0};

//VARIABLES
unsigned long contador_tiempo = 0;
unsigned long timer_letra = 0;
int letra = 25;
int correcta = 0;
boolean activa_letra = false;
int bloquea[NFRASE] = {-1,-1,-1,-1,-1,-1,-1};

//OBJETOS
CapacitiveSensor   capi = CapacitiveSensor(CAPNI,CAPI);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   capd = CapacitiveSensor(CAPNI,CAPD); 
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
//declara salidas
  for(int a = 0;a < N_OUTPUTS;a++){ 
    pinMode(OUTPUTS[a] , OUTPUT);
    digitalWrite(OUTPUTS[a] , OUTPUTS_ISTATE[a]);
  }
//si necesita reposo
  if(NEED_REPOSO){reposo=true;activo=false;resuelto=false;}else{reposo=false;activo=true;resuelto=false;}
//EDITABLE 
  FastLED.addLeds<WS2812, PIXE, RGB>(leds, 26);
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
    if(correcta == NFRASE){ouija_ok = true;}
    if (ouija_ok){
      activo = false;
      resuelto = true;
      digitalWrite(REL1,LOW);
      for(int i = 0;i<26;i++){
        color(i,4,0,false);}
      FastLED.show();
    }
     letreando();
  }
}

void if_resuelto()
{
  if(resuelto){
    delay(30000);
    correcta = 0;
    resuelto = false;
    activo = true;
    activa_letra = false;
    bloquea[0]=-1;
    bloquea[1]=-1;
    bloquea[2]=-1;
    bloquea[3]=-1;
    bloquea[4]=-1;
    bloquea[5]=-1;
    bloquea[6]=-1;
    digitalWrite(REL1,HIGH);
      for(int i = 0;i<26;i++){
        color(i,0,0,false);}
      FastLED.show();
    }
  }


void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    Serial.println(letra);
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
  delay(25);
  return resu;
}

void movete(int letter)
{
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
    bloquea[6]=-1;}
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
      leds[led] = CRGB ::Red;
      break;

    case 5 :
      leds[led] = CRGB ::Yellow;
      break;
    
    case 6 :
      leds[led] = CRGB ::Green;
      break;
  
   case 7 :
      leds[led] = CRGB ::Blue;   
      break; 
    }}
