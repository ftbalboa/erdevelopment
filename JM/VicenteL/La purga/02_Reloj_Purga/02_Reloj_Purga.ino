/* 02_Reloj
 * 27/6/18
 * 
 * UNO CON ETHERNET SHIELD, SE CONECTA
 * A SERVER CON IP ESTABLECIDA
 * CONTROLA UNA MATRIX PIXEL LED
 * 
 * 
 * 1.0 alpha
 */
/////////INCLUDES////////////
#include <Ethernet.h>
#include <SPI.h>

//////////DEFINES////////////
#define tiempo_total 3599
#include "FastLED.h"
#define DATA_PIN 5
#define NUM_LEDS 30
//////////EDITABLES//////////
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x12 };        //diferente en todos los devices, programable en router
byte ip[] = { 192, 168, 0, 112};                            //101 es el server
byte server[] = { 192, 168, 0, 110};                    
const char  PASO_ACTIVACION = '1';
const char  PASO_RESOLUCION = 'Z';
const char RESPUESTA = 'Z';
const char RESET = 'R';
const char VUELTA = 'V';
const char TIEMPO = 'T';
boolean first_reset = false;
boolean first_time = true;
//////////NO EDITABLES///////
unsigned long contador = 0;
boolean activo = false;
boolean resuelto = false;
boolean reset = false;
boolean reposo = false;
boolean eth_on = false;

////////CHOCLO///////////////
EthernetClient client;
CRGB leds[NUM_LEDS];
/////GLOBALES EDITABLES//////
int HOR_FIN = 0;
int SEG_FIN = 0;
int MIN_FIN = 0;
int SEG_RES = 0;
int C_TIMER = 0;
unsigned int tiempo_restante = 3599;
unsigned long contador_tiempo = 0;
char toString[5] = {'T','6','0','0','0'};
////////SETUP////////////////
void setup() {
  delay(5000);                                                  //delay inicial
  Serial.begin(9600);                                           //serial
  if (Ethernet.begin(mac) == 0) {                               //I
    Serial.println("Failed to configure Ethernet using DHCP");  //N
  }                                                             //T
  printIPAddress();                                                             //T
///////////////SETUP EDITABLE//////////////////////
FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
color(28,4,0,false);
color(29,4,0,false);
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
  if ((millis() - contador) >= 1100) { // Esto lo puedes dejar como estaba, pero creo que es más ilustrativo así
    contador = millis();
    if(eth_on == false){
      if (client.connect("192.168.0.110", 24)){eth_on = true;}
      }else{
        char c = client.read();
        while(c != -1){
          if(c == PASO_ACTIVACION && resuelto == false || c == '2' && resuelto == false || c == '3' && resuelto == false || c == '4' && resuelto == false || c == '5' && resuelto == false || c == '6' && resuelto == false || c == '7' && resuelto == false ){activo = true; reposo = false;}
          if(c == RESET && reposo == false){reset = true; activo = false; resuelto = false; reposo = false;}
          if(c == PASO_RESOLUCION){if(resuelto){/*client.write(RESPUESTA);*/}}
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
    first_time = true;
    tiempo_restante = 3599;
    actualiza();
    FastLED.show();
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
      if(first_time){contador_tiempo = millis(); first_time = false;
        }
    if ((millis() - contador_tiempo) >= 1000) {        //
      contador_tiempo = contador_tiempo + 1000;
     // Serial.println(tiempo_restante);
      if(tiempo_restante != 0){
        tiempo_restante = tiempo_restante - 1;
        actualiza();
        FastLED.show();
      }else{}
    }  
  }
}
//resuelto
void if_resuelto()
{
  if(resuelto){
  /////////EDITAR COSAS A HACER RESUELTO//////
    
    }
}

void segmentacion (int NUMERO , int LED_INICIO) {

  switch(NUMERO){

      case 0:
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

      segmentacion (decenas , C_TIMER);

      segmentacion (unidades , C_TIMER + 7);

      decenas = MIN_FIN / 10;

      unidades = MIN_FIN - decenas * 10;

      segmentacion (decenas , C_TIMER +14);

      segmentacion (unidades , C_TIMER + 21);      
      
      }else{
        
      decenas = MIN_FIN / 10;

      unidades = MIN_FIN - decenas * 10;

      segmentacion (decenas , C_TIMER);

      segmentacion (unidades , C_TIMER + 7);

      decenas = SEG_FIN / 10;

      unidades = SEG_FIN - decenas * 10;

      segmentacion (decenas , C_TIMER +14);

      segmentacion (unidades , C_TIMER + 21);  
      
        }
    
    }
  
  }
