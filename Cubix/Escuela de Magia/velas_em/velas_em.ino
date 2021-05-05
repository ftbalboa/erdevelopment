/* Velas EM
 * 
 * Arduino NANO,  4 RS, 1 RELES, 4 PIXEL
 * 
 * reinicia con power up
 * 
 * Sputnik 14/9/19
 */

//INCLUDES
#include <FastLED.h>

//DEFINES
#define SPRINT      true
#define NEED_REPOSO false

#define NLED        4

#define RED1        4
#define RED2        5
#define RED3        6
#define RED4        7
#define PIXE        3
#define REL1        2

#define NCOLORES    8

#define DS  200

#define TIEMPO_LETRA    1000

//CONSTANTES
const int N_INPUTS = 4;
const int INPUTS[N_INPUTS] = {RED1,RED2,RED3,RED4};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1,1};
const int N_OUTPUTS = 1;
const int OUTPUTS[N_OUTPUTS] = {REL1};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1};


//VARIABLES
unsigned long contador_tiempo = 0;
int color_actual[NLED] = {5,5,5,5};

//OBJETOS

CRGB leds[NLED];

//NO EDITABLE
boolean reposo = false;
boolean activo = false;
boolean resuelto = false;
unsigned long timer_print = 0;
////////////////////////////////////SETUP///////////////////////////////
//NO EDITABLE
void setup() {
  if(SPRINT){Serial.begin(9600);} 
//declara entradas
  for(int a = 0;a < N_INPUTS;a++){ 
    pinMode(INPUTS[a] , INPUT);
    digitalWrite(INPUTS[a] , INPUTS_ISTATE[a]);
  }
//declara salidas
  for(int a = 0;a < N_OUTPUTS;a++){ 
    pinMode(OUTPUTS[a] , OUTPUT);
    digitalWrite(OUTPUTS[a] , OUTPUTS_ISTATE[a]);
  }
//si necesita reposo
  if(NEED_REPOSO){reposo=true;activo=false;resuelto=false;}else{reposo=false;activo=true;resuelto=false;}
//EDITABLE
 
  FastLED.addLeds<NEOPIXEL, PIXE>(leds, 26);
  FastLED.setBrightness(  124 );
  for(int i = 0;i<NLED;i++){
    color(i,color_actual[i],0,false);}
  FastLED.show();
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
  if(reposo){
  }
}

void if_activo()
{
  if(activo){
    for(int i = 0;i < NLED;i++){
      if(check(0,INPUTS[i],DS)){color_actual[i]=color_actual[i]++;if(color_actual[i]==NCOLORES){color_actual[i]=0;}
      
      }}
    for(int i = 0;i<NLED;i++){
      color(i,color_actual[i],0,false);}
      
//      activo = false;
//      resuelto = true;
      digitalWrite(REL1,HIGH);
//      myDFPlayer.loop(3);

      FastLED.show();

  }
}

void if_resuelto()
{
  if(resuelto){
    digitalWrite(REL1,LOW);
  }
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    timer_print = millis();
    
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
      leds[led] = CRGB ::LightSkyBlue;
      break;

    case 4 :
      leds[led] = CRGB ::Green;
      break;

    case 5 :
      leds[led] = CRGB ::Yellow;
      break;
    
    case 6 :
      leds[led] = CRGB ::Red;
      break;
  
   case 7 :
      leds[led] = CRGB ::Blue;   
      break; 
    }}
