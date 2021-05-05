/* Velas Nosferatu
 * 
 * Arduino UNO, DOS LEDS, UN RS, UN RELE, Y una palanca
 * Cuando se cierra el rs se prende un led y se activa el rele
 * si se activa la palanca pasa lo mismo.
 */
 
 
//EDITABLE
#define SPRINT      true
#define NEED_REPOSO false
#define LED0        4
#define LED1        3
#define RS          9
#define PALA        6
#define RELE        8

#define DS  50

const int N_INPUTS = 2;
const int INPUTS[N_INPUTS] = {RS,PALA};
const int INPUTS_ISTATE[N_INPUTS] = {1,1};
const int N_OUTPUTS = 3;
const int OUTPUTS[N_OUTPUTS] = {LED0,LED1,RELE};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {0,1,1};


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
    if(check(0,RS,DS) || check(0,PALA,DS)){activo = false;resuelto = true;digitalWrite(RELE,LOW);digitalWrite(LED0,HIGH);}
  }
}
void if_resuelto()
{
  if(resuelto){
    
  }
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    Serial.println(check(0,RS,DS));
    timer_print = millis();
    
    }
  }

//NO EDITABLE
//comprueba el estado de un sensor
boolean check (boolean cual, int entrada, int ds)
{
  boolean resu = false;
  int contador = 0;  
  if(cual){ while(digitalRead(entrada) == 1 && resu == false){/*delay(ds);*/contador++;if(contador == ds){resu = true;}}
  }else{    while(digitalRead(entrada) == 0 && resu == false){/*delay(ds);*/contador++;if(contador == ds){resu = true;}}}  
  return resu; 
}
