/* costom_clock
 * 05/04/19
 * 
 * Nano con 3 botones
 * controla tira de pixel reloj.
 * BOT0 play/pause
 * BOT1 +1 MIN
 * BOT2 -1 MIN
 * 1.0 alpha
 */
 
//////////DEFINES////////////
#include "FastLED.h"
#define DATA_PIN  2
#define NUM_LEDS  28
#define BOT0  5
#define BOT1  4
#define BOT2  3
#define DS    200 
#define TIEMPO_MAX  356400 
#define TIEMPO_MIN  0
#define BRIGHTNESS  64
//////////NO EDITABLES///////
unsigned long contador = 0;
CRGB leds[NUM_LEDS];
int HOR_FIN = 0;
int SEG_FIN = 0;
int MIN_FIN = 0;
int SEG_RES = 0;
int C_TIMER = 0;
unsigned int tiempo_total = 3599;
unsigned int tiempo_restante = 3599;
unsigned long contador_tiempo = 0;
char toString[5] = {'T','6','0','0','0'};
boolean play = false;
boolean ret_play = false;
////////SETUP////////////////
void setup() {
  delay(1000);                                                  //delay inicial
  Serial.begin(9600);                                           //serial
  Serial.println("START");
  pinMode(BOT0 , INPUT);
  digitalWrite(BOT0 , HIGH);
  pinMode(BOT1 , INPUT);
  digitalWrite(BOT1 , HIGH);
  pinMode(BOT2 , INPUT);
  digitalWrite(BOT2 , HIGH);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );
  actualiza();
  FastLED.show();
//////////////////////////////////////////////////
}
/////////////////////LOOP/////////////////////////
void loop() {
  buttons();
  relojea();
}
//////////////////////NO EDITABLE/////////////////


//////////////////FUNCIONES NO EDITABLES/////////////////
//botonea
void buttons()
{
  if(check(0,BOT0,DS)){if(ret_play){play = !play;ret_play = false;full(28,0,0,0);FastLED.show();pierdeTiempo(3);actualiza();FastLED.show();}}else{ret_play = true;}
  if(check(0,BOT1,DS) && !play){if(tiempo_total < TIEMPO_MAX){tiempo_total = (tiempo_total / 60)*60+60;tiempo_restante = tiempo_total;actualiza();FastLED.show();Serial.println(tiempo_total);pierdeTiempo(2);}}else{}
  if(check(0,BOT2,DS) && !play){if(tiempo_total > TIEMPO_MIN){tiempo_total = (tiempo_total / 60)*60-60;tiempo_restante = tiempo_total;actualiza();FastLED.show();pierdeTiempo(2);}}else{}
}

//activo
void relojea()
{
  if(play){
    if ((millis() - contador_tiempo) >= 1000) {        //
      contador_tiempo = millis();
      Serial.println(tiempo_restante);
      if(tiempo_restante != 0){
        tiempo_restante = tiempo_restante - 1;
        actualiza();
        FastLED.show();
      }
    }  
  }
}


void segmentacion (int NUMERO , int LED_INICIO) {

  switch(NUMERO){

    //RELOJ PIXEL
/*    
    case 0:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,0,0,false);
    break;
    
    case 1:
    color(LED_INICIO,0,0,false);
    color(LED_INICIO+1,0,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,0,0,false);
    color(LED_INICIO+5,0,0,false);
    color(LED_INICIO+6,0,0,false);
    break;    
    
    case 2:
    color(LED_INICIO,0,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,0,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,4,0,false);
    break;

    case 3:
    color(LED_INICIO,0,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,0,0,false);
    color(LED_INICIO+6,4,0,false);
    break;

    case 4:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,0,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,0,0,false);
    color(LED_INICIO+5,0,0,false);
    color(LED_INICIO+6,4,0,false);
    break;

    case 5:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,0,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,0,0,false);
    color(LED_INICIO+6,4,0,false);
    break;
    
    case 6:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,0,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,4,0,false);
    break;    

    case 7:
    color(LED_INICIO,0,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,0,0,false);
    color(LED_INICIO+5,0,0,false);
    color(LED_INICIO+6,0,0,false);
    break;

    case 8:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,4,0,false);
    break;

    case 9:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,0,0,false);
    color(LED_INICIO+6,4,0,false);
    break;
    }*/
/*
    //RELOJ PIXEL INVERTIDO
    case 0:
    color(LED_INICIO,0,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,4,0,false);
    break;
    
    case 1:
    color(LED_INICIO,0,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,0,0,false);
    color(LED_INICIO+3,0,0,false);
    color(LED_INICIO+4,0,0,false);
    color(LED_INICIO+5,0,0,false);
    color(LED_INICIO+6,4,0,false);
    break;    
    
    case 2:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,0,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,0,0,false);
    break;

    case 3:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,0,0,false);
    color(LED_INICIO+4,0,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,4,0,false);
    break;

    case 4:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,0,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,0,0,false);
    color(LED_INICIO+5,0,0,false);
    color(LED_INICIO+6,4,0,false);
    break;

    case 5:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,0,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,0,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,4,0,false);
    break;
    
    case 6:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,0,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,4,0,false);
    break;    

    case 7:
    color(LED_INICIO,0,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,0,0,false);
    color(LED_INICIO+4,0,0,false);
    color(LED_INICIO+5,0,0,false);
    color(LED_INICIO+6,4,0,false);
    break;

    case 8:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,4,0,false);
    break;

    case 9:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,0,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,4,0,false);
    break;
    }*/
  
    //RELOJ PIXEL NORMAL DADO VUELTA
    
    case 0:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,0,0,false);
    break;
    
    case 1:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,0,0,false);
    color(LED_INICIO+2,0,0,false);
    color(LED_INICIO+3,0,0,false);
    color(LED_INICIO+4,0,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,0,0,false);
    break;    
    
    case 2:
    color(LED_INICIO,0,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,0,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,4,0,false);
    break;

    case 3:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,0,0,false);
    color(LED_INICIO+3,0,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,4,0,false);
    break;

    case 4:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,0,0,false);
    color(LED_INICIO+2,0,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,0,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,4,0,false);
    break;

    case 5:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,0,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,0,0,false);
    color(LED_INICIO+6,4,0,false);
    break;
    
    case 6:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,0,0,false);
    color(LED_INICIO+6,4,0,false);
    break;    

    case 7:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,0,0,false);
    color(LED_INICIO+2,0,0,false);
    color(LED_INICIO+3,0,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,0,0,false);
    break;

    case 8:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,4,0,false);
    break;

    case 9:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,0,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,4,0,false);
    break;
    }
  
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

void actualiza(){

  SEG_RES = tiempo_restante; /*- segundos*/;

  if(SEG_RES >= 0){

    int probador = 0;

    probador = SEG_RES / 3600;

    HOR_FIN = 0;
      
    while(probador >= 1){HOR_FIN++;probador--;}
      
    probador = (SEG_RES - HOR_FIN * 3600) / 60;

    MIN_FIN = 0;
      
    while(probador >= 1){MIN_FIN++;probador--;}

    SEG_FIN = SEG_RES - HOR_FIN * 3600 - MIN_FIN * 60;
    
    int decenas = 0;
    int unidades = 0;

    if(HOR_FIN > 0){
      
      decenas = HOR_FIN / 10;

      unidades = HOR_FIN - decenas * 10;
//NORMAL
/*
      segmentacion (decenas , C_TIMER);

      segmentacion (unidades , C_TIMER + 7);

      decenas = MIN_FIN / 10;

      unidades = MIN_FIN - decenas * 10;

      segmentacion (decenas , C_TIMER +14);

      segmentacion (unidades , C_TIMER + 21); 
      */    
       
// NORMAL DADO VUELTA
      segmentacion (decenas , C_TIMER + 21);

      segmentacion (unidades , C_TIMER + 14);

      decenas = MIN_FIN / 10;

      unidades = MIN_FIN - decenas * 10;

      segmentacion (decenas , C_TIMER + 7);

      segmentacion (unidades , C_TIMER);      
      
      }else{
        
      decenas = MIN_FIN / 10;

      unidades = MIN_FIN - decenas * 10;

//NORMAL
/*
      segmentacion (decenas , C_TIMER);

      segmentacion (unidades , C_TIMER + 7);

      decenas = SEG_FIN / 10;

      unidades = SEG_FIN - decenas * 10;

      segmentacion (decenas , C_TIMER +14);

      segmentacion (unidades , C_TIMER + 21); 
      */    
       
// NORMAL DADO VUELTA
      segmentacion (decenas , C_TIMER + 21);

      segmentacion (unidades , C_TIMER + 14);

      decenas = SEG_FIN / 10;

      unidades = SEG_FIN - decenas * 10;

      segmentacion (decenas , C_TIMER + 7);

      segmentacion (unidades , C_TIMER);  
      
        }
    
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
//pierde tiempo en milisegundos
void pierdeTiempo (unsigned long cienmilis)
{
  unsigned int tiempo_perdido = 0;
  unsigned long cuenta = millis();
  while(cienmilis > tiempo_perdido){
    if ((millis() - cuenta) >= 100) {
      cuenta = millis();
      tiempo_perdido++;
    }  
  }
  return 0;
}

void full (int cantidad , int led_inicio , int col , int tiempo){
  
  boolean imprimir = true;
  
    int  c = 0;

  if (tiempo == 0){imprimir = false;}

  while(c < (cantidad)) {

    color(led_inicio + c , col, tiempo, imprimir);
    
    c++;

    
    }
  
 // if(tiempo == 0){FastLED.show();}
  
  }
