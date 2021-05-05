//INCLUDES
#include "FastLED.h"

boolean W_COLOR = false;
int L_ADN = 22;
int C_ADN = 0;
int paso_secuencia = 0;

#define NUM_LEDS 22
#define DATA_PIN 3
#define CLOCK_PIN 13
CRGB leds[NUM_LEDS];

int caminito = 0;
int caminito_ant1 = 0;
int caminito_ant2 = 0;
int caminito_ant3 = 0;

boolean green = false;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

}

void loop() {
  
  adnUpdate();
  FastLED.show();
  delay(150);
  adnUpdate();
  FastLED.show();
  if(paso_secuencia == 6){paso_secuencia = 6;}else{paso_secuencia++;}
  delay(150);
}

 void adnUpdate (){

        switch(paso_secuencia){
          
          case 0:
         /*color(C_ADN+paso_secuencia,6,0,false);
                      color(C_ADN+11+paso_secuencia,7,0,false);*/
                      full(L_ADN-11-paso_secuencia,C_ADN+paso_secuencia,0,0);
                      full(L_ADN-11-paso_secuencia,C_ADN+paso_secuencia+11,0,0);
          
          break;

          case 1:
          if(W_COLOR){color(C_ADN+0,6,0,false);
                      color(C_ADN+11+0,7,0,false);
                   /*   full(L_ADN-11-paso_secuencia,C_ADN+paso_secuencia,0,0);
                      full(L_ADN-11-paso_secuencia,C_ADN+paso_secuencia+11,0,0);*/}
          else{
                      color(C_ADN+0,7,0,false);
                      color(C_ADN+11+0,6,0,false);
                   /*   full(L_ADN-11-paso_secuencia,C_ADN+paso_secuencia,0,0);
                      full(L_ADN-11-paso_secuencia,C_ADN+paso_secuencia+11,0,0);*/}
          break;

          case 2:
          if(W_COLOR){color(C_ADN+0,6,0,false);
                      color(C_ADN+11+0,7,0,false);
                      color(C_ADN+1,7,0,false);
                      color(C_ADN+11+1,6,0,false);
                      color(C_ADN+2,6,0,false);
                      color(C_ADN+11+2,7,0,false);
                   /*   full(L_ADN-12-paso_secuencia*2,C_ADN+paso_secuencia+1,0,0);
                      full(L_ADN-12-paso_secuencia*2,C_ADN+paso_secuencia+12,0,0);*/}
          else{       color(C_ADN+0,7,0,false);
                      color(C_ADN+11+0,6,0,false);
                      color(C_ADN+1,6,0,false);
                      color(C_ADN+11+1,7,0,false);
                      color(C_ADN+2,7,0,false);
                      color(C_ADN+11+2,6,0,false);
                     /* full(L_ADN-12-paso_secuencia*2,C_ADN+paso_secuencia+1,0,0);
                      full(L_ADN-12-paso_secuencia*2,C_ADN+paso_secuencia+12,0,0);*/}
          break;

          case 3:
          if(W_COLOR){color(C_ADN+0,6,0,false);
                      color(C_ADN+11+0,7,0,false);
                      color(C_ADN+1,7,0,false);
                      color(C_ADN+11+1,6,0,false);
                      color(C_ADN+2,6,0,false);
                      color(C_ADN+11+2,7,0,false);
                      color(C_ADN+3,6,0,false);
                      color(C_ADN+11+3,7,0,false);
                      color(C_ADN+4,7,0,false);
                      color(C_ADN+11+4,6,0,false);
                      /*full(L_ADN-12-paso_secuencia,C_ADN+paso_secuencia+1,0,0);
                      full(L_ADN-12-paso_secuencia,C_ADN+paso_secuencia+12,0,0);*/}
          else{       color(C_ADN+0,7,0,false);
                      color(C_ADN+11+0,6,0,false);
                      color(C_ADN+1,6,0,false);
                      color(C_ADN+11+1,7,0,false);
                      color(C_ADN+2,7,0,false);
                      color(C_ADN+11+2,6,0,false);
                      color(C_ADN+3,7,0,false);
                      color(C_ADN+11+3,6,0,false);
                      color(C_ADN+4,6,0,false);
                      color(C_ADN+11+4,7,0,false);
                      /*full(L_ADN-12-paso_secuencia,C_ADN+paso_secuencia+1,0,0);
                      full(L_ADN-12-paso_secuencia,C_ADN+paso_secuencia+12,0,0);*/}
          break;

          case 4:
          if(W_COLOR){color(C_ADN+0,6,0,false);
                      color(C_ADN+11+0,7,0,false);
                      color(C_ADN+1,7,0,false);
                      color(C_ADN+11+1,6,0,false);
                      color(C_ADN+2,6,0,false);
                      color(C_ADN+11+2,7,0,false);
                      color(C_ADN+3,6,0,false);
                      color(C_ADN+11+3,7,0,false);
                      color(C_ADN+4,7,0,false);
                      color(C_ADN+11+4,6,0,false);
                      color(C_ADN+5,7,0,false);
                      color(C_ADN+11+5,6,0,false);
                      color(C_ADN+6,6,0,false);
                      color(C_ADN+11+6,7,0,false);
                     /* full(L_ADN-12-paso_secuencia,C_ADN+paso_secuencia+1,0,0);
                      full(L_ADN-12-paso_secuencia,C_ADN+paso_secuencia+12,0,0);*/}
          else{       color(C_ADN+0,7,0,false);
                      color(C_ADN+11+0,6,0,false);
                      color(C_ADN+1,6,0,false);
                      color(C_ADN+11+1,7,0,false);
                      color(C_ADN+2,7,0,false);
                      color(C_ADN+11+2,6,0,false);
                      color(C_ADN+3,7,0,false);
                      color(C_ADN+11+3,6,0,false);
                      color(C_ADN+4,6,0,false);
                      color(C_ADN+11+4,7,0,false);
                      color(C_ADN+5,6,0,false);
                      color(C_ADN+11+5,7,0,false);
                      color(C_ADN+6,7,0,false);
                      color(C_ADN+11+6,6,0,false);
                     /* full(L_ADN-12-paso_secuencia,C_ADN+paso_secuencia+1,0,0);
                      full(L_ADN-12-paso_secuencia,C_ADN+paso_secuencia+12,0,0);*/}
          break;

          case 5:
          if(W_COLOR){color(C_ADN+0,6,0,false);
                      color(C_ADN+11+0,7,0,false);
                      color(C_ADN+1,7,0,false);
                      color(C_ADN+11+1,6,0,false);
                      color(C_ADN+2,6,0,false);
                      color(C_ADN+11+2,7,0,false);
                      color(C_ADN+3,6,0,false);
                      color(C_ADN+11+3,7,0,false);
                      color(C_ADN+4,7,0,false);
                      color(C_ADN+11+4,6,0,false);
                      color(C_ADN+5,7,0,false);
                      color(C_ADN+11+5,6,0,false);
                      color(C_ADN+6,6,0,false);
                      color(C_ADN+11+6,7,0,false);
                      color(C_ADN+7,6,0,false);
                      color(C_ADN+11+7,7,0,false);
                      color(C_ADN+8,7,0,false);
                      color(C_ADN+11+8,6,0,false);
                   /*   full(L_ADN-12-paso_secuencia,C_ADN+paso_secuencia+1,0,0);
                      full(L_ADN-12-paso_secuencia,C_ADN+paso_secuencia+12,0,0);*/}
          else{       color(C_ADN+0,7,0,false);
                      color(C_ADN+11+0,6,0,false);
                      color(C_ADN+1,6,0,false);
                      color(C_ADN+11+1,7,0,false);
                      color(C_ADN+2,7,0,false);
                      color(C_ADN+11+2,6,0,false);
                      color(C_ADN+3,7,0,false);
                      color(C_ADN+11+3,6,0,false);
                      color(C_ADN+4,6,0,false);
                      color(C_ADN+11+4,7,0,false);
                      color(C_ADN+5,6,0,false);
                      color(C_ADN+11+5,7,0,false);
                      color(C_ADN+6,7,0,false);
                      color(C_ADN+11+6,6,0,false);
                      color(C_ADN+7,7,0,false);
                      color(C_ADN+11+7,6,0,false);
                      color(C_ADN+8,6,0,false);
                      color(C_ADN+11+8,7,0,false);
                     /* full(L_ADN-12-paso_secuencia,C_ADN+paso_secuencia+1,0,0);
                      full(L_ADN-12-paso_secuencia,C_ADN+paso_secuencia+12,0,0);*/}
          break;

          case 6:
          /*if(W_COLOR){/*color(C_ADN+0,6,0,false);
                      color(C_ADN+11+0,6,0,false);
                      color(C_ADN+1,7,0,false);
                      color(C_ADN+11+1,7,0,false);
                      color(C_ADN+2,6,0,false);
                      color(C_ADN+11+2,6,0,false);
                      color(C_ADN+3,7,0,false);
                      color(C_ADN+11+3,7,0,false);
                      color(C_ADN+4,6,0,false);
                      color(C_ADN+11+4,6,0,false);
                      color(C_ADN+5,7,0,false);
                      color(C_ADN+11+5,7,0,false);
                      color(C_ADN+6,6,0,false);
                      color(C_ADN+11+6,6,0,false);
                      color(C_ADN+7,7,0,false);
                      color(C_ADN+11+7,7,0,false);
                      color(C_ADN+8,6,0,false);
                      color(C_ADN+11+8,6,0,false);
                      color(C_ADN+9,7,0,false);
                      color(C_ADN+11+9,7,0,false);
                      color(C_ADN+10,6,0,false);
                      color(C_ADN+11+10,6,0,false);*/
                     /* full(L_ADN-12-paso_secuencia*2,C_ADN+paso_secuencia+1,0,0);
                      full(L_ADN-12-paso_secuencia*2,C_ADN+paso_secuencia+12,0,0);*//*}
          else{ */ 
                if(green){

                    if(caminito != 50 && caminito != 11){      
                        color(C_ADN+caminito,7,0,false);}
                       
                        if(caminito > 1 && caminito_ant1 != 50 && caminito_ant1 != 11){
                          color(C_ADN+caminito_ant1,7,0,false);}
                        if(caminito_ant1 > 1 && caminito_ant2 != 50 && caminito_ant2 != 11){
                          color(C_ADN+caminito_ant2,7,0,false);}
                        if(caminito_ant2 > 1 && caminito_ant3 != 50 && caminito_ant3 != 11){
                          color(C_ADN+caminito_ant3,0,0,false);}
                        caminito_ant3=caminito_ant2;
                        caminito_ant2=caminito_ant1;
                        caminito_ant1=caminito;
                      if(caminito%2 != 0){caminito =caminito+11;}else{caminito =caminito-9;}
                      if(caminito > 20){caminito = 50;if(caminito_ant3 == 50){green=false; caminito =0;caminito_ant1=0;caminito_ant2=0;caminito_ant3=0;}}                
                      
                      }else{
                       if(caminito != 50 && caminito != 12){      
                        color(C_ADN+caminito,6,0,false);}
                       
                        if(caminito > 0 && caminito_ant1 != 50 && caminito_ant1 != 12){
                          color(C_ADN+caminito_ant1,6,0,false);}
                        if(caminito_ant1 > 0 && caminito_ant2 != 50 && caminito_ant2 != 12){
                          color(C_ADN+caminito_ant2,6,0,false);}
                        if(caminito_ant2 > 0 && caminito_ant3 != 50 && caminito_ant3 != 12){
                          color(C_ADN+caminito_ant3,0,0,false);}
                        caminito_ant3=caminito_ant2;
                        caminito_ant2=caminito_ant1;
                        caminito_ant1=caminito;
                      if(caminito%2 == 0){caminito =caminito+11;}else{caminito =caminito-9;}
                      if(caminito > 21){caminito = 50;if(caminito_ant3 == 50){green=true; caminito =1;caminito_ant1=0;caminito_ant2=0;caminito_ant3=0;}}}
                    /*  color(C_ADN+11+0,7,0,false);
                      color(C_ADN+1,6,0,false);
                      color(C_ADN+11+1,6,0,false);
                      color(C_ADN+2,7,0,false);
                      color(C_ADN+11+2,7,0,false);
                      color(C_ADN+3,6,0,false);
                      color(C_ADN+11+3,6,0,false);
                      color(C_ADN+4,7,0,false);
                      color(C_ADN+11+4,7,0,false);
                      color(C_ADN+5,6,0,false);
                      color(C_ADN+11+5,6,0,false);
                      color(C_ADN+6,7,0,false);
                      color(C_ADN+11+6,7,0,false);
                      color(C_ADN+7,6,0,false);
                      color(C_ADN+11+7,6,0,false);
                      color(C_ADN+8,7,0,false);
                      color(C_ADN+11+8,7,0,false);
                      color(C_ADN+9,6,0,false);
                      color(C_ADN+11+9,6,0,false);
                      color(C_ADN+10,7,0,false);
                      color(C_ADN+11+10,7,0,false);*/
                     /* full(L_ADN-12-paso_secuencia*2,C_ADN+paso_secuencia+1,0,0);
                      full(L_ADN-12-paso_secuencia*2,C_ADN+paso_secuencia+12,0,0);}*/
          break;
          }
  
  W_COLOR = !W_COLOR;
  
  
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
    
    
    
    }


    if(col != 0 && col != 1 && imprimir){  FastLED.show();delay(tiempo);}
  
  

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
