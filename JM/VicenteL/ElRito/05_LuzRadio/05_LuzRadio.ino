/* 05_LuzRadio
 * 04/6/18
 * 
 * UNO CON ETHERNET SHIELD, SE CONECTA
 * A SERVER CON IP ESTABLECIDA
 * CONTROLA UN DFPLAYER, Y UNA PIXEL
 * 
 * 
 * 0.1 alpha
 */
/////////INCLUDES////////////
#include <Ethernet.h>
#include <SPI.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "FastLED.h"
//////////DEFINES EDITABLES////////////
//dfplayer
#define RX_DFP_PIN  2
#define TX_DFP_PIN  3
//fastled
#define NUM_LEDS 94
#define DATA_PIN 5
#define CLOCK_PIN 13
//////////EDITABLES//////////
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x05 };        //diferente en todos los devices, programable en router
byte ip[] = { 192, 168, 0, 105};                            //101 es el server
byte server[] = { 192, 168, 0, 101};                    
const char  PASO_ACTIVACION = '5';
const char  PASO_RESOLUCION = '5';
const char  RESPUESTA = '5';
const char  RESET = 'R';
//////////NO EDITABLES///////
unsigned long contador = 0;
boolean activo = false;
boolean resuelto = false;
boolean reset = false;
boolean reposo = false;
boolean eth_on = false;
boolean first_time_activo = true;
boolean first_time_resuelto = true;
////////CHOCLO///////////////
EthernetClient client;
CRGB leds[NUM_LEDS];
//declaraciones dfplayer
 /******AUDIOS******
1-Primer tema
2-Disco
  ******************/
SoftwareSerial mySoftwareSerial(2, 3); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
/////GLOBALES EDITABLES//////
const int TIEMPO_PARPADEO = 100;
boolean flag0 = true;
boolean flag7 = true;
boolean first_song = true;
unsigned long contador_song = 0;
unsigned long contador_parpadeo = 0;
////////SETUP////////////////
void setup() {
  delay(1000);                                                  //delay inicial
  Serial.begin(9600);                                           //serial
  if (Ethernet.begin(mac) == 0) {                               //I
    Serial.println("Failed to configure Ethernet using DHCP");  //N
  }                                                             //T
  printIPAddress();
  {
}                                                             
///////////////SETUP EDITABLE//////////////////////
  //MP3
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
      Serial.println(F("Unable to begin:"));
      Serial.println(F("1.Please recheck the connection!"));
      Serial.println(F("2.Please insert the SD card!"));
  }
  myDFPlayer.volume(20);  //Set volume value. From 0 to 30
  //fastled
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  full(NUM_LEDS,0,0,0);
  FastLED.show();
//////////////////////////////////////////////////
}
/////////////////////LOOP/////////////////////////
void loop() {
  eth_update();
  if_reset();
  if_reposo();
  if_activo();
  if_resuelto();
}
//////////////////////NO EDITABLE/////////////////
//imprime ip
void printIPAddress()
{
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }

  Serial.println();
}
//actualiza eth
void eth_update()
{
  if ((millis() - contador) >= 500) { // Esto lo puedes dejar como estaba, pero creo que es más ilustrativo así
    contador = millis();
    if(eth_on == false){
      if (client.connect("192.168.0.101", 23)){eth_on = true;}
      }else{
        char c = client.read();
        while(c != -1){
          if(c == PASO_ACTIVACION && resuelto == false || c == PASO_RESOLUCION && resuelto == false){activo = true; reposo = false;}
          if(c == RESET && reposo == false){reset = true; activo = false; resuelto = false; reposo = false;}
          if(c == PASO_RESOLUCION){if(resuelto){/*client.write(RESPUESTA);*/}else{activo=true;reposo=false;}}
          if(c == '7'){if(flag7){full (NUM_LEDS , 0 , 4 , 0);FastLED.show();resuelto=true;activo=false;flag7=false;}}
          Serial.println(c);
          c = client.read();
          eth_on = false;c = -1;
      }
      if(eth_on == false){client.stop();contador = millis();}
    }
  }
}
//////////////////EDITAR/////////////////
//reset
void if_reset ()
{
  if(reset){
    reset = false;
    reposo = true;
    first_time_activo = true;
    first_time_resuelto = true;
    //EDITAR A COSAS A RESETEAR
    full (NUM_LEDS , 0 , 0 , 0);
    FastLED.show();
    flag0 = true;
    flag7 = true;
  }
}
//reposo
void if_reposo()
{
  if(reposo){
   /////////EDITAR COSAS A HACER EN REPOSO////
    
    }
}
//activo
void if_activo()
{
  if(activo){
  ////////EDITAR A COSAS A HACER CUANDO SE ACTIVA///// 
    if(first_time_activo){
      first_time_activo = false;
      //EDITAR A COSAS A HACER LA PRIMERA VEZ QUE SE ACTIVA//
      myDFPlayer.play(1);
      contador_song = millis();
      first_song=true;
      full (NUM_LEDS , 0 , 3 , 0);  
      FastLED.show();
    }

  if(millis()-contador_song > 244000 && first_song){
    myDFPlayer.loop(2);
    first_song = false;
    }
    parpadeo();
  }
}
//resuelto
void if_resuelto()
{
  if(resuelto){
  /////////EDITAR COSAS A HACER RESUELTO//////
    if(first_time_resuelto){
      first_time_resuelto = false;
      //EDITAR A COSAS A HACER LA PRIMERA VEZ
      }
    }
}

//FUNCIONES ESPECIFICAS
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
  }

void parpadeo() 
{
  if(millis() - contador_parpadeo > 10000){
    full(NUM_LEDS, 0, 0, 0);
    FastLED.show();
    delay(200);
    full(NUM_LEDS, 0, 2, 0);
    FastLED.show();
    delay(100);
    full(NUM_LEDS, 0, 0, 0);
    FastLED.show();
    delay(100);
    full(NUM_LEDS, 0, 2, 0);
    FastLED.show();
    delay(200);
    full(NUM_LEDS, 0, 0, 0);
    FastLED.show();
    delay(300);
    full(NUM_LEDS, 0, 2, 0);
    FastLED.show();
    delay(50);
    full(NUM_LEDS, 0, 0, 0);
    FastLED.show();
    delay(100);   
    full(NUM_LEDS, 0, 2, 0);
    FastLED.show();
    contador_parpadeo = millis();
    }
}
