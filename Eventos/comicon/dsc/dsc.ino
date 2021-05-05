/* Evento comicon disneychanell
 * DSC
 * MEGA, botones UNL20003 y rele 
 * 5/12/18
 */

//CONSTANTES
//EDITABLE
#define SPRINT              false
#define N_PASOS             1
#define TIEMPO_PARPADEO     4000
#define TIEMPO_RESET        3000
#define TIEMPO_FIN          10000
#define CL                  43
#define CB                  44
#define UNL1                29
#define UNL2                30
#define UNL3                31
#define UNL4                32
#define UNL5                33
#define UNL6                34
#define UNL7                35
#define UNL8                36
#define UNL9                37
#define UNL10               38
#define UNL11               39
#define UNL12               40
#define UNL13               41
#define UNL14               42
#define RCMFIN              45
#define B1                  9
#define B2                  8
#define B3                  7
#define B4                  6
#define B5                  5
#define B6                  4
#define B7                  3
#define B8                  22
#define B9                  23
#define B10                 24
#define B11                 25
#define B12                 26
#define B13                 27
#define B14                 28

#define DS  0


const int N_INPUTS = 15;
const int INPUTS[N_INPUTS] = {CB,B1,B2,B3,B4,B5,B6,B7,B8,B9,B10,B11,B12,B13,B14};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
const int N_OUTPUTS = 16;
const int OUTPUTS[N_OUTPUTS] = {CL,RCMFIN,UNL1, UNL2, UNL3, UNL4, UNL5, UNL6, UNL7,UNL8,UNL9,UNL10,UNL11,UNL12,UNL13,UNL14};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//GLOBALES
int lugar_secuencia = 0;
const int LARGO_SECUENCIA = 12;
const int SECUENCIA [LARGO_SECUENCIA] ={3,0,5,2,1,4,9,6,7,10,11,8};
const int REF = 1;
const int REF2 = B8;
const int REF_UNL = UNL1;
const int N_BOTO = 12;
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
}

///////////////////////////////////////LOOP//////////////////////////////////////////
void loop() {
  boolean change = false;
 // paso_actual = control_base(paso_actual);
  if(paso_anterior != paso_actual){change = true;paso_anterior = paso_actual;}
  paso_actual = game(paso_actual,change);
 // showme();
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
  if(cual){ while(digitalRead(entrada) == 1 && resu == false){contador++;if(contador == 1500){resu = true;}}
  }else{    while(digitalRead(entrada) == 0 && resu == false){contador++;if(contador == 1500){resu = true;}}}  
  return resu; 
}

//EDITABLE

int game(int paso_actual, boolean change)
{
  switch(paso_actual){   

    case 0:
      if(change){reset_game();}
      for(int i = 0; i < N_BOTO;i++){
        if(check(0,INPUTS[REF+i],DS) && bot_ant != i){
          bot_ant = i;
          if(SECUENCIA[lugar_secuencia] == i){
            digitalWrite(REF_UNL+i,HIGH);
            lugar_secuencia++;
            }else {
              for(int i = 0; i < N_BOTO;i++){digitalWrite(REF_UNL+i,LOW);lugar_secuencia = 0;}}
        }
        
        }
      if(lugar_secuencia == LARGO_SECUENCIA){paso_actual++;}
      break;
    
    }
//FIN
  if(paso_actual >= N_PASOS){paso_actual = 0;digitalWrite(RCMFIN,LOW);delay(TIEMPO_FIN);reset_game();}

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
    //Serial.print("Actual: ");
    //Serial.println(actual);
    timer_print = millis();  
    }
  }
