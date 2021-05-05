/* Reloj_pixel
 * 16/09/18
 * 
 * Nano con sensor ventana
 * controla tira de pixel reloj.
 * 
 * 1.0 alpha
 */
 
//////////DEFINES////////////
#define tiempo_total 3600
#include "FastLED.h"
#define DATA_PIN 5
#define NUM_LEDS 30
#define IMAN 3
//////////NO EDITABLES///////
unsigned long contador = 0;
CRGB leds[NUM_LEDS];
int HOR_FIN = 0;
int SEG_FIN = 0;
int MIN_FIN = 0;
int SEG_RES = 0;
int C_TIMER = 0;
unsigned int tiempo_restante = 3600;
unsigned long contador_tiempo = 0;
char toString[5] = {'T','6','0','0','0'};
boolean play = false;
////////SETUP////////////////
void setup() {
  delay(1000);                                                  //delay inicial
  Serial.begin(9600);                                           //serial
  pinMode(IMAN , INPUT);
  digitalWrite(IMAN , HIGH);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  color(14,4,0,false);
  color(15,4,0,false);
//////////////////////////////////////////////////
}
/////////////////////LOOP/////////////////////////
void loop() {
  check();
  relojea();
}
//////////////////////NO EDITABLE/////////////////


//////////////////FUNCIONES NO EDITABLES/////////////////
//check
void check()
{
  if(digitalRead(IMAN) == false){delay(30);if(digitalRead(IMAN) == false){play = true;}}else{play = false;tiempo_restante = tiempo_total;}
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
    }

    //RELOJ PIXEL INVERTIDO
    /*case 0:
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

      segmentacion (decenas , C_TIMER);

      segmentacion (unidades , C_TIMER + 7);

      decenas = MIN_FIN / 10;

      unidades = MIN_FIN - decenas * 10;

      segmentacion (decenas , C_TIMER +16);

      segmentacion (unidades , C_TIMER + 23);      
      
      }else{
        
      decenas = MIN_FIN / 10;

      unidades = MIN_FIN - decenas * 10;

      segmentacion (decenas , C_TIMER);

      segmentacion (unidades , C_TIMER + 7);

      decenas = SEG_FIN / 10;

      unidades = SEG_FIN - decenas * 10;

      segmentacion (decenas , C_TIMER +16);

      segmentacion (unidades , C_TIMER + 23);  
      
        }
    
    }
  
  }
