/* Servidor Faraon
 * 
 * Arduino MEGA,   12 reles
 * 1 485 RX
 * 
 * Sputnik 23/12/20
 */



 //INCLUDES
#include <Wire.h>

//DEFINES
#define SPRINT      true
#define NEED_REPOSO true

#define ARPA        22
#define OJO         23
#define ESCA        24
#define PIRA        25
#define FUEG        26
#define DES1        27
#define MAMU        28
#define TUMBA       29
#define DES2        30
#define DISC        31
#define ATAR        32
#define TALI        33

#define DS          200

#define DISCOS      2

//CONSTANTES
const int N_INPUTS = 1;
const int INPUTS[N_INPUTS] = {DISCOS};
const int INPUTS_ISTATE[N_INPUTS] = {1};
const int N_OUTPUTS = 12;
const int OUTPUTS[N_OUTPUTS] = {ARPA,OJO,ESCA,PIRA,FUEG,MAMU,TUMBA,DISC,TALI,DES1,ATAR,DES2};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,1,1,1,1,1,1,1,1,1,1,0};


//VARIABLES
unsigned long contador_tiempo = 0;
unsigned int input_state = 0;
unsigned int input_futuro = 0;
byte orden = 99; 
char recibi = 0;

bool ojo = false;
bool discos = false;

//OBJETOS


//NO EDITABLE
unsigned long timer_print = 0;

////////////////////////////////////SETUP///////////////////////////////
//NO EDITABLE
void setup() {
  delay(1000);
  if(SPRINT){Serial1.begin(9600);Serial.begin(9600);} 
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

//EDITABLE 

}

///////////////////////////////////////LOOP//////////////////////////////////////////
void loop() {
 // Serial.println(analogBeast());
 // delay(500);
  levanta();
  showme();
  input_a_rele();
  juego();
}

////////////////////////////////////////FUNCIONES///////////////////////////////////
//EDITABLE


void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
   timer_print = millis();
    }
  }


void levanta()
{
  while(Serial1.available()){
    char inp = Serial1.read();
    switch(inp){
      
      case 'I':
        orden = 4;
        input_futuro = 0;
        break;

      case 'F':
        if(orden == 0){input_state = input_futuro; input_futuro = 0;/*Serial.print(" // "); Serial.println(input_state);*/} orden = -1;
        break;  

      default:
        if(orden > -1){
          int exponente = 1;
          for(int i = orden-1; i>0;  i--){exponente = exponente * 10;}
          int num = inp - 48;
          //Serial.print(num);
          //Serial.print(" = ");
          //Serial.print(exponente);
          //Serial.print(" || ");
          input_futuro = input_futuro + num * exponente; 
          orden--; 
        }
        break;
      
      }
    }
}

void input_a_rele()
{
   for(int i = 0;i<N_OUTPUTS;i++){
    if(OUTPUTS[i] == DES2){}else{
    if(OUTPUTS[i] == OJO && ojo || OUTPUTS[i] == DISC && discos){digitalWrite(OUTPUTS[i],0);}else{
      digitalWrite (OUTPUTS[i],!bitRead(input_state,i));
      if(OUTPUTS[i] == ATAR && bitRead(input_state,i)){resetea();}}}
  }  
}

void resetea()
{
  ojo = false;
  discos = false;
  digitalWrite(ARPA, LOW);
  digitalWrite(MAMU, LOW);
  digitalWrite(TALI,LOW);
  digitalWrite(PIRA,LOW);
  }

void juego()
{
  if(check(0,DISCOS,DS)){discos = true;}
  if(analogBeast() < 20){ojo =true;}
  }

int analogBeast(){
  unsigned long promedio= 0;
  int limite = 1000;
  for(int i = 0; i < limite; i++){
    promedio += analogRead(A0);   
    }
  promedio = promedio / limite;//Serial.println(promedio);
  return promedio;
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
