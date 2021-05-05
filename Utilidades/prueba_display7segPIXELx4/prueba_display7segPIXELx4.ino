#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 30

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 5
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

int TIEMPO = 0;
int HOR_FIN = 0;
int SEG_FIN = 0;
int MIN_FIN = 0;
int SEG_RES = 0;
int C_TIMER = 0;


void setup() { 
      // Uncomment/edit one of the following lines for your leds arrangement.
      // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  	  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
      // FastLED.addLeds<APA104, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);
      
      // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<DOTSTAR, RGB>(leds, NUM_LEDS);

      // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
        color(14,4,0,false);
        color(15,4,0,false);
}

void loop() { 
  // Turn the LED on, then pause
/*  leds[0] = CRGB::Red;
  leds[1] = CRGB::Red;
  leds[2] = CRGB::Red;
  leds[3] = CRGB::Red;
  leds[4] = CRGB::Red;
  leds[5] = CRGB::Red;
  leds[6] = CRGB::Red;*/


  // Now turn the LED off, then pause
 // leds[0] = CRGB::Black;
  FastLED.show();
  delay(250);
  TIEMPO++;
  actualiza();
}

void segmentacion (int NUMERO , int LED_INICIO) {

  switch(NUMERO){

 /*     case 0:
    color(LED_INICIO,4,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,0,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,4,0,false);
    break;
    
    case 1:
    color(LED_INICIO,0,0,false);
    color(LED_INICIO+1,0,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,0,0,false);
    color(LED_INICIO+4,0,0,false);
    color(LED_INICIO+5,0,0,false);
    color(LED_INICIO+6,4,0,false);
    break;    
    
    case 2:
    color(LED_INICIO,0,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,4,0,false);
    color(LED_INICIO+5,4,0,false);
    color(LED_INICIO+6,0,0,false);
    break;

    case 3:
    color(LED_INICIO,0,0,false);
    color(LED_INICIO+1,4,0,false);
    color(LED_INICIO+2,4,0,false);
    color(LED_INICIO+3,4,0,false);
    color(LED_INICIO+4,0,0,false);
    color(LED_INICIO+5,4,0,false);
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
    color(LED_INICIO+4,0,0,false);
    color(LED_INICIO+5,4,0,false);
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
    break;*/
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

  SEG_RES = TIEMPO /*- segundos*/;

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
