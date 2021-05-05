/* Evento comicon disneychanell
 *
 * 5/12/18
 */
 
//INCLUDES


//CONSTANTES

 
//EDITABLE
#define SPRINT              false
#define N_PASOS             2
#define TIEMPO_PARPADEO     4000
#define TIEMPO_RESET        3000
#define TIEMPO_FIN          10000
#define CL                  10
#define CB                  10

#define DS  30


const int N_INPUTS = 1;
const int INPUTS[N_INPUTS] = {CB};
const int INPUTS_ISTATE[N_INPUTS] = {1};
const int N_OUTPUTS = 1;
const int OUTPUTS[N_OUTPUTS] = {CL};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {0};

//GLOBALES



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
      if(change){reset_game();}
      break;

     case 1:
      if(change){}
      break;
    
    }

  if(paso_actual >= N_PASOS){paso_actual = 0;delay(TIEMPO_FIN);}

  return paso_actual;

}

void reset_game()
{
    for(int a = 0;a < N_OUTPUTS;a++){ 
    digitalWrite(OUTPUTS[a] , OUTPUTS_ISTATE[a]);
  }
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
