//INCLUDES
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "FastLED.h"

//DEFINES Y COSAS FASTLED

#define NUM_LEDS 272
#define DATA_PIN 2
#define CLOCK_PIN 13
CRGB leds[NUM_LEDS];
int ledau = 0;
#define cled  8
#define na  3
#define am  2
#define ro  1
#define ne  0
#define vel 100

 int sierra[cled] = {na , na , na , na , na , na , na , na};

 int sierra_blin [cled] = {am , am , am , am , am ,am , am , am};

 int blank [cled] =  {ne , ne , ne , ne , ne , ne ,ne ,ne};

//DECLARACIONES LIB.MP3

 /******AUDIOS******
  1-SIERRA + ALARMA 
  2-ALARMA
  3-C4
  ******************/

SoftwareSerial mySoftwareSerial(13, 3); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

//BOOLEANS

boolean needreset = true;

//PINOUT
int rx1 = 12;
int rx2 = 11;
int rele = 7;
int iman = 4;

//SETUP
void setup() {

    //DELAY INICIAL
    delay(1000);

    //LEDS
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  

    //MP3
    mySoftwareSerial.begin(9600);
    Serial.begin(9600);
    if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
      Serial.println(F("Unable to begin:"));
      Serial.println(F("1.Please recheck the connection!"));
      Serial.println(F("2.Please insert the SD card!"));
      while(true);


  }
    //pinModes
    pinMode(rele, OUTPUT);
    pinMode(iman, INPUT);
    pinMode(rx1, INPUT);
    pinMode(rx2, INPUT);
    digitalWrite(rele, HIGH);
    digitalWrite(iman, HIGH);  
     Serial.println(F("DFPlayer Mini online."));

     myDFPlayer.volume(20);  //Set volume value. From 0 to 30

       blanc(272 , 0);
  FastLED.show();
}


//LOOP
void loop() {
    

      if( digitalRead(rx1)){

        delay(100);

        if(digitalRead(rx1)){

        delay(4000);

        myDFPlayer.loop(2);

        delay(15000);

        Serial.print("entre a");

        myDFPlayer.loop(1);

        delay(5000);

        while (ledau < 264 ){


  int a = 0;

  while(a < cled ) {

    color(ledau+a , sierra[a]);
    
    a++;

    
    }

  a = 0;

  

 FastLED.show();

  delay(vel/2);


   while(a < (cled)) {

    color(ledau+a , sierra_blin[a]);
    
    a++;

    
    }



  color(ledau-1 , ne);

    ledau++;

  FastLED.show();

  delay(vel/2);
  Serial.println(ledau);
  
}

 blanc(272 , 0);
  FastLED.show();

        myDFPlayer.pause();

        digitalWrite(rele,LOW);

        delay(1000);

        digitalWrite(rele , HIGH );

        needreset = false;

        ledau = 0;
        
        }
      }

      if( digitalRead(rx2)){

        delay(100);

        if(digitalRead(rx2)){

        Serial.print("entre b");

        myDFPlayer.loop(2);

        boolean hola = true;

        while (hola){if(digitalRead(iman) == 0){delay(200);if(digitalRead(iman) == 0){hola = false;}}}

        myDFPlayer.play(3);

        delay(7000);

        full(NUM_LEDS,0,4);
        
        FastLED.show();
    
        delay (4000);

        digitalWrite(rele , LOW );

        delay(1000);

        digitalWrite(rele , HIGH );

        blanc(NUM_LEDS,0);

        FastLED.show();

        needreset = false;
        
        }



      
  }

  Serial.println("");   // salto de linea monitor serial

    
  delay(125);                 // Pausa antes repetir el ciclo

  delay(125);                 // Pausa antes repetir el ciclo
  
  }


//FUNCIONES

//-----apaga----

  void blanc (int cantidad , int led_inicio){
  
  
    int  c= 0;


  while(c < (cantidad)) {

    color(led_inicio + c , ne);
    
    c++;

    
    }
  
  
  
  }



//---color-----

void color (int led , int col) {
  
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

      leds[led] = CRGB ::Orange;

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
    
    
    }
  
  

  }

     void full (int cantidad , int led_inicio , int col){
  
  
    int  c= 0;


  while(c < (cantidad)) {

    color(led_inicio + c , col);
    
    c++;

    
    }
  
  
  
  }
