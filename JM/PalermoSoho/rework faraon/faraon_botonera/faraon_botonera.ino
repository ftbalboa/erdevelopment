/* Botonera Faraon
 * 
 * Arduino NANO,   11 palancas, 1 buzzer
 * 1 485
 * 
 * Sputnik 23/12/20
 */



 //INCLUDES
#include <Wire.h>

//DEFINES
#define SPRINT      true
#define NEED_REPOSO true

#define BUZZ        3

#define PAL1        2
#define PAL2        14
#define PAL3        7
#define PAL4        8
#define PAL5        10
#define PAL6        4
#define PAL7        5
#define PAL8        6
#define PAL9        9
#define PAL10       11

#define PALR        12

#define DS          200

#define SEGURO      4

//CONSTANTES
const int N_INPUTS = 11;
const int INPUTS[N_INPUTS] = {PAL1,PAL2,PAL3,PAL4,PAL5,PAL6,PAL7,PAL8,PAL9,PAL10,PALR};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1,1,1,1,1,1,1,1,1};
const int N_OUTPUTS = 1;
const int OUTPUTS[N_OUTPUTS] = {BUZZ};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {0};


//VARIABLES
unsigned long contador_tiempo = 0;
int input_state = 0;


//OBJETOS


//NO EDITABLE
boolean reposo = false;
boolean activo = true;
boolean resuelto = false;
unsigned long timer_print = 0;
////////////////////////////////////SETUP///////////////////////////////
//NO EDITABLE
void setup() {
  delay(1000);
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
  tone(BUZZ,350);     // tono de pulsacion
  delay(200);
  noTone(BUZZ);

//EDITABLE
 

}

///////////////////////////////////////LOOP//////////////////////////////////////////
void loop() {

  levanta();
  showme();
}

////////////////////////////////////////FUNCIONES///////////////////////////////////
//EDITABLE


void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
   int resto = 0;
   byte mil = 0;
   byte cen = 0;
   byte dec = 0;
   byte uni = 0;
   mil    = input_state/1000;
   resto  = input_state - mil * 1000;
   cen    = resto/100;
   resto  = resto - cen * 100;
   dec    = resto/10;
   resto  = resto - dec * 10;
   uni    = resto;

   for(int i =  0; i < 6 ; i++){
     switch(i){
      case 0:
       Serial.print('I');
       break;
      case 1:
       Serial.write(mil+48);
       break;
      case 2:
       Serial.write(cen+48);
       break;
      case 3:
       Serial.write(dec+48);
       break;
      case 4:
       Serial.write(uni+48);
       break;
      case 5:
       Serial.print('F');
       break;
     }
       unsigned int limite = 15000;
       unsigned int pierdetiempo =0;
       while(pierdetiempo<limite){pierdetiempo++;}
       pierdetiempo = 0;
   }
   timer_print = millis();
    }
  }


void levanta()
{
  int new_input_state = 0;
  for(int i = 0;i<N_INPUTS;i++){
     bitWrite(new_input_state,i,check(0,INPUTS[i],DS));
  } 
  int  palancas = 0;
   for(int i = 0;i<N_INPUTS-1;i++){
     if(bitRead(new_input_state,i)){palancas++;};
  }
  if(palancas > SEGURO){tone(BUZZ,440);}
    else{
   for(int i = 0;i<N_INPUTS;i++){
     if(bitRead(new_input_state,i) != bitRead(input_state,i) && bitRead(new_input_state,i) && i != N_INPUTS-1){tone(BUZZ,500);delay(100);noTone(BUZZ);tone(BUZZ,650);delay(100);};
     if(bitRead(new_input_state,i) != bitRead(input_state,i) && !bitRead(new_input_state,i)&& i != N_INPUTS-1){tone(BUZZ,650);delay(100);noTone(BUZZ);tone(BUZZ,500);delay(100);};
     if(bitRead(new_input_state,i) != bitRead(input_state,i) && bitRead(new_input_state,i) && i == N_INPUTS-1){tone(BUZZ,200);delay(300);noTone(BUZZ);tone(BUZZ,400);delay(300);};
     if(bitRead(new_input_state,i) != bitRead(input_state,i) && !bitRead(new_input_state,i) && i == N_INPUTS-1){tone(BUZZ,400);delay(300);noTone(BUZZ);tone(BUZZ,200);delay(300);};
  }
      input_state= new_input_state;
      noTone(BUZZ);} 
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
