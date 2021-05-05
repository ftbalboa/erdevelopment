/*
PINOUTS

BOTONES 4-12 Y DEL 14-18

*/

//INCLUDES

#include "FastLED.h"

//DEFINES BOTONES

#define N_BOTONES 14

#define CORRIMIENTO 4         // desplazamiento del 0 a la hora de nombrar botones en el pinout

#define EXCEPCION 13          //pin 13 no puede usarse con pull up

//DEFINES RELES

#define HUEVO_NEGRO 13 

#define HUEVO_ROJO 2 

//VARIABLES GLOBALES

int boton_actual = -1;

int boton_anterior = -1;

int cantidad_de_secuencias = 1;

int secuencia_actual = 0;

int secuencia1 [7] ={1,5,2,0,6,3,4};
int secuencia12 [7] ={1,5,2,0,6,3,4};
int secuencia2 [7] ={10,11,7,13,8,12,9};
int secuencia22 [7] ={10,11,7,13,8,12,9};
int secuenciar [7] ={1,8,2,9,3,10,0};

int posicion_actual = 0;

int secuencia = 0; // 0 sin secuencia, 1 secuencia1 , 2 secuencia2, 3 secuenciar, 4 secuencia12 , 5 secuencia 22

boolean do_nothing = false;

//preposo
boolean reposo = true;
boolean change = false;
int reposo_delay = 0;
int ldp = 0;
int ldc = 0;
int r = 2;
int g = 0;
int b = 2;

//VARIABLES Y DEFINE FASTLED

int paso_rojo[7] = { 1 , 11 , 23 , 36 , 48 , 57 , 65}; // cantidad de leds a encender

int paso_negro[7] = { 1 , 4 , 19 , 28 , 37 , 55 , 63}; // idem

int contoneo = 0;

boolean change_b = true;

#define ARRANCA_NEGRO 65

#define NUM_LEDS 128
#define DATA_PIN 3
#define CLOCK_PIN 3
CRGB leds[NUM_LEDS];
int ledau = 0;
#define cled  8
#define bl  3
#define am  2
#define ro  1
#define ne  0
#define vel 2

//SETUP

void setup() {

  //LEDS
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);


  //BOTONES
  int while_botones = -1;

  while(while_botones < N_BOTONES){
    
    while_botones++;
    if((while_botones + CORRIMIENTO) < EXCEPCION){
    pinMode(while_botones + CORRIMIENTO , INPUT);
    digitalWrite(while_botones + CORRIMIENTO , HIGH);
    }else{
    pinMode(while_botones + CORRIMIENTO + 1 , INPUT);
    digitalWrite(while_botones + CORRIMIENTO + 1 , HIGH);
      }
    
    }


  //RELES
  pinMode(HUEVO_ROJO , OUTPUT);
  digitalWrite(HUEVO_ROJO , HIGH);
  pinMode(HUEVO_NEGRO , OUTPUT);
  digitalWrite(HUEVO_NEGRO , HIGH);

  blanc(NUM_LEDS , 0);

  
  //SERIAL DE PRUEBA
    Serial.begin(9600);
  Serial.println("INICIO"); //prueba
}

//LOOP

void loop() {

  boton_actual = check_button_state(N_BOTONES);

  if(boton_actual == boton_anterior){do_nothing = true; delay(100);}
  else{do_nothing = false; delay(100);boton_anterior = boton_actual;}

  if(do_nothing == false && boton_actual != -1){

    if(reposo) {reposo = false;blanc(NUM_LEDS , 0); }
    
      Serial.println(boton_actual); //prueba
      
    switch(secuencia){
      
      case 0:

          if(boton_actual == secuencia1[0]){secuencia = 1; actualizar(secuencia , posicion_actual , paso_rojo); posicion_actual++;}
          if(boton_actual == secuencia2[0]){secuencia = 2; actualizar(secuencia , posicion_actual , paso_negro); posicion_actual++;}

        break;

      case 1:
     Serial.println("posicion_actual"); //prueba Serial.println(posicion_actual); //prueba
          if(boton_actual == secuencia1[posicion_actual]){actualizar(secuencia , posicion_actual , paso_rojo); posicion_actual++;}
          else{secuencia = 0; posicion_actual = 0; blanc(NUM_LEDS , 0);  FastLED.show();}
          if(posicion_actual == 7){if(cantidad_de_secuencias == 1){digitalWrite(HUEVO_ROJO , LOW); secuencia = 3;posicion_actual=0;}
          
          else{ secuencia = 4;posicion_actual=0; }
          
          }
          
        break;
      
      case 2:

          if(boton_actual == secuencia2[posicion_actual]){actualizar(secuencia , posicion_actual , paso_negro); posicion_actual++;}
          else{secuencia = 0; posicion_actual = 0; blanc(NUM_LEDS , 0);  FastLED.show();}
          if(posicion_actual == 7){if(cantidad_de_secuencias == 1){digitalWrite(HUEVO_NEGRO , LOW); secuencia = 3;posicion_actual=0;}
          
          else{secuencia = 5; posicion_actual=0;}
          
          }
          
        break;

      case 3:

          if(boton_actual == secuenciar[posicion_actual]){posicion_actual++;}
          else{posicion_actual = 0;}
          if(posicion_actual == 7){digitalWrite(HUEVO_ROJO , HIGH);digitalWrite(HUEVO_NEGRO , HIGH);secuencia=0;posicion_actual=0; blanc(NUM_LEDS , 0);  FastLED.show(); reposo = true;}

        break;

      case 4:

          if(boton_actual == secuencia12[posicion_actual]){actualizar(secuencia , posicion_actual , paso_rojo); posicion_actual++;}
          else{secuencia = 0; posicion_actual = 0; blanc(NUM_LEDS , 0);  FastLED.show();}
          if(posicion_actual == 7){digitalWrite(HUEVO_ROJO , LOW); secuencia = 3;posicion_actual=0;}

        break;

      case 5:

          if(boton_actual == secuencia22[posicion_actual]){actualizar(secuencia , posicion_actual , paso_negro); posicion_actual++;}
          else{secuencia = 0; posicion_actual = 0; blanc(NUM_LEDS , 0);  FastLED.show();}
          if(posicion_actual == 7){digitalWrite(HUEVO_NEGRO , LOW); secuencia = 3;posicion_actual=0;}

        break;
        
    
    }
    
    }

    if(do_nothing && reposo){

    if (reposo_delay > 0){

      if(ldp == NUM_LEDS + 31 ){ldp = 0;}

    if(ldp < NUM_LEDS){

    color(ldp , 3 , 0 , false);

    }

    if(ldp > 30){color(ldp-31 , 0 , 0 , false);}
    
    reposo_delay = 0;
    FastLED.show();
    ldp++;
    }

    

    reposo_delay++;

    }

   if(digitalRead(HUEVO_ROJO) == false){delay(50);if(contoneo == 5){if(change_b){change_b = false; full(65,0,4,0);}else{change_b = true; full(65,0,0,0);}contoneo=0;}contoneo++;}
   if(digitalRead(HUEVO_NEGRO) == false){delay(50);if(contoneo == 5){if(change_b){change_b = false; full(63,65,3,0);}else{change_b = true; blanc(128,0);}contoneo=0;}contoneo++;}
   
}

//FUNCIONES

int check_button_state (int cantidad) {

  int boton_presionado = -1;
  int while_botones = -1;
  boolean presionaron = false;

  while((while_botones < cantidad) && (presionaron == false)){

   while_botones++;

  if((while_botones + CORRIMIENTO) < 13){
  
   if (digitalRead(while_botones + CORRIMIENTO) == false){
    
      presionaron = true;
      boton_presionado = while_botones;
    
      }

  }else{
    
       if (digitalRead(while_botones + CORRIMIENTO + 1) == false){
    
      presionaron = true;
      boton_presionado = while_botones;
    
      }
    
    
    }

    }


   return boton_presionado;
  
  }

  void actualizar (int secuencia_actualizar , int paso , int pasos[7]){

    int leds_encender = 0;

    int paso_anterior = 0;

    if(paso != 0){paso_anterior = pasos[paso - 1];}

    leds_encender = pasos[paso] - paso_anterior;
    
    switch(secuencia_actualizar){
      
      case 1:

            if(paso == 0){full(leds_encender , 0 , 4 , vel);}

            else{full(leds_encender , pasos[paso-1] , 4 , vel);}

        break;
      
      case 2:

            if(paso == 0){full(leds_encender , ARRANCA_NEGRO , 3 , vel);}

            else{full(leds_encender , ARRANCA_NEGRO + pasos[paso-1] , 3 , vel);}

        break;      
      
      case 3:

        break;

      case 4:

     

            if(paso == 0){leds_encender = pasos[paso];full(leds_encender , 0 , 6 , vel);}

            else{full(leds_encender , pasos[paso-1] , 6 , vel);}

        break;

      case 5:


            if(paso == 0){full(leds_encender , ARRANCA_NEGRO , 7 , vel);}

            else{full(leds_encender , ARRANCA_NEGRO + pasos[paso-1] , 7 , vel);}

        break;
      
      }
    
    
    
    }

//funciones FASTLED

//-----apaga----

  void blanc (int cantidad , int led_inicio){
  
  
    int  c= 0;


  while(c < (cantidad)) {

    color(led_inicio + c , ne , 0 , false);
    
    c++;

    
    }
  
  FastLED.show();

  
  }



//---color-----

void color (int led , int col , int tiempo , boolean imprimir) {
  
  switch (col){

    case 0 : 

      leds[led] = CRGB ::Black;

    break;
    
    case 1 :

      leds[led] = CRGB ::Black;

 /*     leds[led].r = 255;
      leds[led].g = 255;
      leds[led].b = 255;*/

    break;

    case 2 :

      leds[led] = CRGB ::DarkOrange;

 /*     leds[led].r = 240;
      leds[led].g = 115;
      leds[led].b = 026;*/

    break;

    case 3 :

      leds[led] = CRGB ::White;

/*      leds[led].r = 152;
      leds[led].g = 061;
      leds[led].b = 014;*/

    break;

        case 4 :

      leds[led] = CRGB ::Red;

/*      leds[led].r = 152;
      leds[led].g = 061;
      leds[led].b = 014;*/

    break;

        case 5 :

      leds[led] = CRGB ::Yellow;

/*      leds[led].r = 152;
      leds[led].g = 061;
      leds[led].b = 014;*/

    break;
    
    case 6 :

      leds[led] = CRGB ::Green;

/*      leds[led].r = 152;
      leds[led].g = 061;
      leds[led].b = 014;*/

    break;

   case 7 :

      leds[led] = CRGB ::Blue;

/*      leds[led].r = 152;
      leds[led].g = 061;
      leds[led].b = 014;*/

    break;
    
    
    
    }


    if(col != 0 && col != 1 && imprimir){  FastLED.show();delay(tiempo);}
  
  

  }

void full (int cantidad , int led_inicio , int col , int tiempo){
  
  boolean imprimir = true;
    int  c= 0;

  if (tiempo == 0){imprimir = false;}

  while(c < (cantidad)) {

    color(led_inicio + c , col, tiempo, imprimir);
    
    c++;

    
    }
  
  if(tiempo == 0){FastLED.show();}
  
  }

 void pinta_rgb (int led ,int r, int g, int b){
  
      leds[led].r = r;
      leds[led].g = g;
      leds[led].b = b;

 }
  
  
  
