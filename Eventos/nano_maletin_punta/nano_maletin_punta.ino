/************************************
* ENVENTO-ALONE                     *
* ---------------------------       *
* ARDUINO NANO - PIXELED            *
* 4 RS, 6 BOTONES                   *
* ---------------------------       *
* Reconoce sensores y botones para  *                 
* llenar una barra de carga, maneja *
* un timer por hora fijable         *
*                                   *
* ----------------------------------*
* V0.01 12/03/2018                  *
*************************************/

//INCLUDES
#include "FastLED.h"
#include <Wire.h>

//DEFINES

//FASTLED

#define NUM_LEDS 56
#define DATA_PIN 3
#define CLOCK_PIN 13
#define C_TUBO 0
#define L_TUBO  4
#define C_ADN 4
#define L_ADN 22
#define C_TIMER 26
#define L_TIMER 30
#define LED_PUNTO 40
CRGB leds[NUM_LEDS];

//PINMODES
#define BUZZER 4
#define RS1 5
#define RS2 6
#define RS3 7
#define RS4 8
#define B1 9
#define B2 10
#define B3 11
#define B4 12
#define B5 14
#define B6 15
#define B7 16

int ds = 10;

//GLOBALES
const unsigned int TIEMPO = 3600; //EN SEGUNDOS
unsigned long segundos = 0 ;
unsigned long contador = 0;
unsigned int SEG_RES = 0;
unsigned int SEG_FIN = 0;
unsigned int HOR_FIN = 0;
unsigned int MIN_FIN = 0;
boolean play = false;
boolean change = false;
boolean W_COLOR = false;
boolean resuelto = false;
boolean cmbio = false;
boolean perdio = false;
boolean rsfirst = false;
int paso_secuencia = 0;
boolean puntito = true;


int caminito = 0;
int caminito_ant1 = 0;
int caminito_ant2 = 0;
int caminito_ant3 = 0;
boolean green = true;
boolean qsyo = true;

boolean sensores[11] = {false, false , false , false , false , false , false , false , false , false, false};
#define N_SENSORES 11

int secuen[6] = {3 , 6 , 5 , 1 , 2 , 4};

//SETUP
void setup() {
    //LEDS
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  // put your setup code here, to run once:
   //Serial.begin(9600) ;
   //Serial.println("empece");
  pinMode(BUZZER, OUTPUT);
  pinMode(RS1, INPUT);
  digitalWrite(RS1, HIGH);
  pinMode(RS2, INPUT);
  digitalWrite(RS2, HIGH);
  pinMode(RS3, INPUT);
  digitalWrite(RS3, HIGH);
  pinMode(RS4, INPUT);
  digitalWrite(RS4, HIGH);
  pinMode(B1, INPUT);
  digitalWrite(B1, HIGH);
  pinMode(B2, INPUT);
  digitalWrite(B2, HIGH);
  pinMode(B3, INPUT);
  digitalWrite(B3, HIGH);
  pinMode(B4, INPUT);
  digitalWrite(B4, HIGH);
  pinMode(B5, INPUT);
  digitalWrite(B5, HIGH);
  pinMode(B6, INPUT);
  digitalWrite(B6, HIGH);
  pinMode(B7, INPUT);
  digitalWrite(B7, HIGH);
  delay(1000);
  full(NUM_LEDS,0,0,0);
  color(LED_PUNTO,4,0,false);
  color(LED_PUNTO+1,4,0,false);
  FastLED.show();
  noTone(BUZZER);   
}


//LOOP
void loop() {
  sensorea();
  beep();
  if(sensores[10]){puntito = true;rsfirst = false;play=true;segundos=0;paso_secuencia = 0;full(NUM_LEDS,0,0,0);resuelto=false;perdio=false;green=true;}
  if(perdio){tone(BUZZER , 1000); delay(200); noTone(BUZZER);delay(200);
  sensorea(); if(sensores[10]){puntito = true; rsfirst = false;play=true;segundos=0;paso_secuencia = 0;full(NUM_LEDS,0,0,0);resuelto=false;perdio=false;green=true;}
  fail();
  }
  if(play){
    if(resuelto == false){
      timer();
    }else{falopeada2();} 
    if(rs_update()){
      if(rsfirst == false){
        rsfirst=true;
        falopeada();
        }
      secuencia();
      adnUpdate ();
    }else{rsfirst = false;}
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

void timer(){
  
   if ((millis() - contador) >= 1000) { // Esto lo puedes dejar como estaba, pero creo que es más ilustrativo así
    contador = millis(); // Aquí estabas perdiendo potencialmente millis, ya que cuando reasignas millis a contador, puede haber pasado alguno más de 1000
    if(segundos == TIEMPO){ if (resuelto==false){perdio = true;}}else{//Serial.println(segundos);
    segundos++;}
    actualiza();
    if(puntito){
    color(LED_PUNTO,4,0,false);
    color(LED_PUNTO+1,4,0,false);
    puntito = false;
    }else{
    color(LED_PUNTO,0,0,false);
    color(LED_PUNTO+1,0,0,false);      
     puntito = true; 
      }
    FastLED.show();
   }
  
  }

void actualiza(){

  SEG_RES = TIEMPO - segundos;

  if(SEG_RES >= 0){

    int probador = 0;

    probador = SEG_RES / 3600;

    HOR_FIN = 0;
      
    while(probador >= 1){HOR_FIN++;probador--;}
      
    probador = (SEG_RES - HOR_FIN * 3600) / 60;

    MIN_FIN = 0;
      
    while(probador >= 1){MIN_FIN++;probador--;}

    SEG_FIN = SEG_RES - HOR_FIN * 3600 - MIN_FIN * 60;
    
/*    Serial.println("hora res");
    Serial.println(HOR_FIN);
    Serial.println("min res");
    Serial.println(MIN_FIN);
    Serial.println("seg res");
    Serial.println(SEG_FIN);*/

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

void segmentacion (int NUMERO , int LED_INICIO) {

  switch(NUMERO){
    
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
  
  
  
  }

boolean check (boolean cual, int entrada, int ds){

  boolean resu = false;
  
  if(cual){ if(digitalRead(entrada) == 1){delay(ds);if(digitalRead(entrada)==1){resu = true;}}
  }else{    if(digitalRead(entrada) == 0){delay(ds);if(digitalRead(entrada)==0){resu = true;}}}
  
  return resu;
  
  }

void sensorea(){
  int a = 0;
  sensores[a] = check(0 , RS1 , ds);

  a++;
  sensores[a] = check(0 , RS2 , ds);

  a++;
  sensores[a] = check(0 , RS3 , ds);

  a++;  
  sensores[a] = check(0 , RS4 , ds);

  a++;
  sensores[a] = check(0 , B1 , ds);

  a++;  
  sensores[a] = check(0 , B2 , ds);

  a++;
  sensores[a] = check(0 , B3 , ds);

  a++;
  sensores[a] = check(0 , B4 , ds);

  a++;  
  sensores[a] = check(0 , B5 , ds);

  a++;
  sensores[a] = check(0 , B6 , ds);

  a++;
  sensores[a] = check(0 , B7 , ds);

  }

  boolean rs_update(){
    boolean resu = false;
    int hola = 0;
    int a = 0;
    if(sensores[a]){color(C_TUBO + a,6,0,false);hola++;}else{color(C_TUBO + a,7,0,false);}
    a++;
    if(sensores[a]){color(C_TUBO + a,6,0,false);hola++;}else{color(C_TUBO + a,7,0,false);}
    a++;
    if(sensores[a]){color(C_TUBO + a,6,0,false);hola++;}else{color(C_TUBO + a,7,0,false);}
    a++;
    if(sensores[a]){color(C_TUBO + a,6,0,false);hola++;}else{color(C_TUBO + a,7,0,false);}
    if(hola == 4){resu = true;}
    return resu;
    }

void secuencia(){
  
    int boton_actual = botonea();

    if(boton_actual != 0){
      if(change){
        
        if(secuen[paso_secuencia] == boton_actual-3){paso_secuencia++;}else{paso_secuencia = 0;}

        adnUpdate();
        
        }
      
      change = false;
      }else{change = true;}
  
  
  }

int botonea(){
    int resu = 0;
  
    int a = 4;
    
    while(a < 10){
      
      if(sensores[a]){resu = a; a = 9;}
      
      a++;
      }
    
    return resu;
    
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
            if(resuelto == false){
                      color(C_ADN+0,6,0,false);
                      color(C_ADN+11+0,6,0,false);
                      color(C_ADN+1,0,0,false);
                      color(C_ADN+11+1,0,0,false);
                      color(C_ADN+2,6,0,false);
                      color(C_ADN+11+2,6,0,false);
                      color(C_ADN+3,0,0,false);
                      color(C_ADN+11+3,0,0,false);
                      color(C_ADN+4,6,0,false);
                      color(C_ADN+11+4,6,0,false);
                      color(C_ADN+5,0,0,false);
                      color(C_ADN+11+5,0,0,false);
                      color(C_ADN+6,6,0,false);
                      color(C_ADN+11+6,6,0,false);
                      color(C_ADN+7,0,0,false);
                      color(C_ADN+11+7,0,0,false);
                      color(C_ADN+8,6,0,false);
                      color(C_ADN+11+8,6,0,false);
                      color(C_ADN+9,0,0,false);
                      color(C_ADN+11+9,0,0,false);
                      color(C_ADN+10,6,0,false);
                      color(C_ADN+11+10,6,0,false);
                      actualiza();
              }
            resuelto = true;
           // segundos = TIEMPO;
            
            switch(caminito){
              
              case 0:
              color(C_ADN+11+9,0,0,false);
              break;

              case 1:
              color(C_ADN+1,7,0,false);
              break;

              case 2:
              color(C_ADN+11+1,7,0,false);

              case 3:
              color(C_ADN+3,7,0,false);
              break;

              case 4:
              color(C_ADN+1,0,0,false);
              color(C_ADN+11+3,7,0,false);
              break;

              case 5:
              color(C_ADN+5,7,0,false);
              color(C_ADN+11+1,0,0,false);
              break;

              case 6:
              color(C_ADN+3,0,0,false);
              color(C_ADN+11+5,7,0,false);
              break;

              case 7:
              color(C_ADN+7,7,0,false);
              color(C_ADN+11+3,0,0,false);
              break;

              case 8:
              color(C_ADN+5,0,0,false);
              color(C_ADN+11+7,7,0,false);
              break;

              case 9:
              color(C_ADN+9,7,0,false);
              color(C_ADN+11+5,0,0,false);
              break;

              case 10:
              color(C_ADN+7,0,0,false);
              color(C_ADN+11+9,7,0,false);
              break;

              case 11:
              //color(C_ADN+7,0,0,false);
              color(C_ADN+11+7,0,0,false);
              break;

              case 12:
              color(C_ADN+9,0,0,false);
              caminito= -1;
              break;


              }
            caminito++;
          /*if(W_COLOR){*//*color(C_ADN+0,6,0,false);
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
          else{ *//* int control = 0;
                while(control != 15){

                    if(caminito != 50 && caminito != 11){      
                        color(C_ADN+caminito,7,0,false);}
                       
                        if(caminito > 1 && caminito_ant1 != 50 && caminito_ant1 != 11){
                          color(C_ADN+caminito_ant1,7,0,false);}
                        if(caminito_ant1 > 1 && caminito_ant2 != 50 && caminito_ant2 != 11){
                          color(C_ADN+caminito_ant2,7,0,false);}
                        if(caminito_ant2 > 1 && caminito_ant3 != 50 && caminito_ant3 != 11){
                         /* color(C_ADN+caminito_ant3,0,0,false);*//*}
                        caminito_ant3=caminito_ant2;
                        caminito_ant2=caminito_ant1;
                        caminito_ant1=caminito;
                      if(caminito%2 != 0){caminito =caminito+11;}else{caminito =caminito-9;}
                      if(caminito > 20){caminito = 50;if(caminito_ant3 == 50){green=false; caminito =0;caminito_ant1=0;caminito_ant2=0;caminito_ant3=0;}}
                      control++;               
                        }*/
                        
              
            /*           if(caminito != 50 && caminito != 12){      
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
                      if(caminito > 21){caminito = 50;if(caminito_ant3 == 50){green=true;qsyo=false; caminito =1;caminito_ant1=0;caminito_ant2=0;caminito_ant3=0;}}}
                      else{if(caminito != 50 && caminito != 12){      
                        color(C_ADN+caminito,6,0,false);}
                       
                        if(caminito > 0 && caminito_ant1 != 50 && caminito_ant1 != 12){
                          color(C_ADN+caminito_ant1,7,0,false);}
                        if(caminito_ant1 > 0 && caminito_ant2 != 50 && caminito_ant2 != 12){
                          color(C_ADN+caminito_ant2,7,0,false);}
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
  
  //W_COLOR = !W_COLOR;
  
   FastLED.show(); 
  }

void beep(){
   if(HOR_FIN == 0 && MIN_FIN < 10 && SEG_FIN%10 == 0 ){
    if(cmbio == false){
     
        tone(BUZZER, 1000);
        delay(50);
        noTone(BUZZER);
        delay(50);
        tone(BUZZER, 1000);
        delay(50);
        noTone(BUZZER);
        delay(50);
        tone(BUZZER, 1000);
        delay(50);
        noTone(BUZZER);
        cmbio = true;  
     }
   
   }else{cmbio = false;}
  }

void buup (){
  
   tone(BUZZER, 1000);
   delay(100);
   noTone(BUZZER);
  
  }

 void fail(){

    int LED_INICIO = C_TIMER;
  
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,0,0,false);
    color(LED_INICIO+3,0,0,false);
    color(LED_INICIO+4,0,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,4,0,false);
  
    LED_INICIO = C_TIMER + 7;

    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,0,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,4,0,false);
  
    LED_INICIO = C_TIMER + 16;

    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,0,0,false);
    color(LED_INICIO+2,0,0,false);
    color(LED_INICIO+3,0,0,false);
    color(LED_INICIO+4,0,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,0,0,false);

    LED_INICIO = C_TIMER + 23;   

    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,0,0,false);
    color(LED_INICIO+2,0,0,false);
    color(LED_INICIO+3,0,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,0,0,false);

    color(LED_PUNTO,0,0,false);
    color(LED_PUNTO+1,0,0,false);

       FastLED.show(); 
  }

 void falopeada(){
  
                      color(C_ADN+0,6,0,false);
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
                      color(C_ADN+11+10,6,0,false);
                       FastLED.show(); 
                      tone(BUZZER , 5000);
                      delay(500);
                      noTone(BUZZER);
                      full(L_ADN,C_ADN,0,0);
                       FastLED.show(); 
                      delay(500);
                      color(C_ADN+0,6,0,false);
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
                      color(C_ADN+11+10,6,0,false);
                       FastLED.show(); 
                      tone(BUZZER , 5000);
                      delay(500);
                      full(L_ADN,C_ADN,0,0);
                      noTone(BUZZER);
  }

void falopeada2 () {
  
    int LED_INICIO = C_TIMER;
  
    color(LED_INICIO,6,0,false);
    color(LED_INICIO+1,0,0,false);
    color(LED_INICIO+2,6,0,false);
    color(LED_INICIO+3,6,0,false);
    color(LED_INICIO+4,0,0,false);
    color(LED_INICIO+5,6,0,false);
    color(LED_INICIO+6,6,0,false);
  
    LED_INICIO = C_TIMER + 7;

    color(LED_INICIO,6,0,false);
    color(LED_INICIO+1,6,0,false);
    color(LED_INICIO+2,6,0,false);
    color(LED_INICIO+3,6,0,false);
    color(LED_INICIO+4,6,0,false);
    color(LED_INICIO+5,6,0,false);
    color(LED_INICIO+6,0,0,false);
  
    LED_INICIO = C_TIMER + 16;

    color(LED_INICIO,6,0,false);
    color(LED_INICIO+1,6,0,false);
    color(LED_INICIO+2,6,0,false);
    color(LED_INICIO+3,0,0,false);
    color(LED_INICIO+4,0,0,false);
    color(LED_INICIO+5,6,0,false);
    color(LED_INICIO+6,6,0,false);

    LED_INICIO = C_TIMER + 23;   

    color(LED_INICIO,6,0,false);
    color(LED_INICIO+1,6,0,false);
    color(LED_INICIO+2,0,0,false);
    color(LED_INICIO+3,0,0,false);
    color(LED_INICIO+4,6,0,false);
    color(LED_INICIO+5,6,0,false);
    color(LED_INICIO+6,6,0,false);

    color(LED_PUNTO,0,0,false);
    color(LED_PUNTO+1,0,0,false);

       FastLED.show(); 
  }
