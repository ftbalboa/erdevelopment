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

#define RED4        4
#define RED3        5
#define RED2        6
#define RED1        7
#define PIXE        3
#define REL1        2

#define NCOLORES    6

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
int color_actual[NLED] = {3,3,3,3};
const int RESPUESTA[NLED] = {1,0,5,4};
boolean retencion[NLED] = {true,true,true,true};

//OBJETOS

CRGB leds[NLED];

//NO EDITABLE
boolean reposo = false;
boolean activo = true;
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
      if(check(0,INPUTS[i],DS)){if(retencion[i]){
        delay(500);
        color_actual[i]= (color_actual[i]+1);if(color_actual[i]==NCOLORES){color_actual[i]=0;}
        retencion[i]=false;
      }
      
      }else{retencion[i]=true;}}
    for(int i = 0;i<NLED;i++){
      color(i,color_actual[i],0,false);}
     FastLED.show();
     int correcta = 0;
    for(int i = 0;i<NLED;i++){
      if(RESPUESTA[i]==color_actual[i]){correcta++;}}  
      if(correcta == NLED){    
        activo = false;
        resuelto = true;
      }



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
    for(int i = 0;i<NLED;i++){
      Serial.println(color_actual[i]);}
    for(int i = 0;i<NLED;i++){
      Serial.println(digitalRead(INPUTS[i]));}
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
      leds[led] = CRGB ::Green;
      break;
    

    case 1 :
      leds[led].setRGB(200,70,255);
      break;

    case 2 :
      leds[led] = CRGB ::Aqua;
      break;

    case 3 :
      leds[led] = CRGB ::Yellow;
      break;
    
   case 4 :
      leds[led] = CRGB ::Red;
      break;
  
   case 5 :
      leds[led] = CRGB ::Blue;   
      break; 
    }}
