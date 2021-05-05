/* Evento comicon disneychanell
 * MICKEY
 * MEGA, botones stepper UNL20003 y rele 
 * 5/12/18
 */
 
//INCLUDES
#include <Stepper.h>

//CONSTANTES
//EDITABLE
#define SPRINT              false
#define N_PASOS             2
#define TIEMPO_PARPADEO     4000
#define TIEMPO_RESET        3000
#define TIEMPO_FIN          10000
#define CL                  24
#define CB                  25
#define RSCLOCK             22
#define BCLOCK              23
#define STEPA               8
#define STEPB               10
#define STEPC               9
#define STEPD               11
#define UNL1                36
#define UNL2                33
#define UNL3                35
#define UNL4                37
#define UNL5                38
#define UNL6                34
#define RCM1                43
#define RCMFIN              42
#define B1                  2
#define B2                  3
#define B3                  4
#define B4                  5
#define B5                  6
#define B6                  7

#define DS  15


const int N_INPUTS = 9;
const int INPUTS[N_INPUTS] = {CB,B1,B2,B3,B4,B5,B6,RSCLOCK,BCLOCK};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1,1,1,1,1,1,1};
const int N_OUTPUTS = 9;
const int OUTPUTS[N_OUTPUTS] = {CL,RCM1,RCMFIN,UNL1, UNL2, UNL3, UNL4, UNL5, UNL6};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {0,1,1,0,0,0,0,0,0};

//GLOBALES
const int stepsPerRevolution = 200; 
Stepper myStepper(stepsPerRevolution, STEPA, STEPB, STEPC, STEPD);
int lugar_secuencia = 0;
const int LARGO_SECUENCIA = 6;
const int SECUENCIA [LARGO_SECUENCIA] ={1,5,2,0,3,4};
const int REF = B1;
const int REF_UNL = 3;
const int N_BOTO = 6;
int bot_ant = 100;
//NO EDITABLE
int paso_actual = 0;
int paso_anterior = 0;
unsigned long timer_print = 0;
unsigned long control_timer = 0;
int contador_control = 0;
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

//EDITABLE
  myStepper.setSpeed(150);
}

///////////////////////////////////////LOOP//////////////////////////////////////////
void loop() {
  boolean change = false;
  paso_actual = control_base(paso_actual);
  if(paso_anterior != paso_actual){change = true;paso_anterior = paso_actual;}
  paso_actual = game(paso_actual,change);
  showme();
}

//NO EDITABLE
int control_base(int paso_actual)
{
  if((millis() - control_timer) > (TIEMPO_PARPADEO/((paso_actual+1)*2)))
  {
    if(contador_control % 2 == 0){
        if(contador_control >= paso_actual*2){digitalWrite(CL , LOW);}else{digitalWrite(CL , HIGH);}
        }else{
          digitalWrite(CL , LOW);}
    contador_control++;
    if(contador_control > (paso_actual+1)*2){contador_control = 0;}
    }

  if(check(0,CB,DS)){
    digitalWrite(CL , HIGH);
    unsigned long reset_timer = millis();
    boolean check_reset = true;
    boolean reset_resu = false;
    while(check_reset){
      check_reset = check(0,CB,DS);
      if((millis() - reset_timer) > TIEMPO_RESET){
        check_reset = false;
        reset_resu = true;
        }
      }
    if(reset_resu){paso_actual = 0;}else{paso_actual++;}
    }
  return paso_actual;
}

boolean check (boolean cual, int entrada, int ds)
{
  boolean resu = false;
  int contador = 0;  
  if(cual){ while(digitalRead(entrada) == 1 && resu == false){delay(ds);contador++;if(contador == 5){resu = true;}}
  }else{    while(digitalRead(entrada) == 0 && resu == false){delay(ds);contador++;if(contador == 5){resu = true;}}}  
  return resu; 
}

//EDITABLE

int game(int paso_actual, boolean change)
{
  switch(paso_actual){
    
    case 0:
      if(change){reset_game(); while(check(0,RSCLOCK,DS)){myStepper.step(1000);}}
      while(check(0,BCLOCK,DS)){myStepper.step(100);delay(1);}
      if(check(0,RSCLOCK,DS)){paso_actual++;}
      break;

    case 1:
      if(change){digitalWrite(RCM1,LOW);}
      for(int i = 0; i < N_BOTO;i++){
        if(check(0,REF+i,DS) && bot_ant != i){
          bot_ant = i;
          if(SECUENCIA[lugar_secuencia] == i){
            digitalWrite(OUTPUTS[REF_UNL+i],HIGH);
            lugar_secuencia++;
            }else {
              for(int i = 0; i < N_BOTO;i++){digitalWrite(OUTPUTS[REF_UNL+i],LOW);lugar_secuencia = 0;}}
        }
        
        }
      if(lugar_secuencia == LARGO_SECUENCIA){paso_actual++;}
      break;
    
    }
//FIN
  if(paso_actual >= N_PASOS){paso_actual = 0;digitalWrite(RCMFIN,LOW);delay(TIEMPO_FIN);}

  return paso_actual;

}

void reset_game()
{
    for(int a = 0;a < N_OUTPUTS;a++){ 
    digitalWrite(OUTPUTS[a] , OUTPUTS_ISTATE[a]);
  }
  lugar_secuencia = 0;
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    Serial.print("Actual: ");
    Serial.println(digitalRead(B2));
    timer_print = millis();  
    }
  }
