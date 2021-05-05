/* Velas Nosferatu
 * 
 * Arduino UNO, DOS LEDS, UN RS, UN RELE, Y una palanca
 * Cuando se cierra el rs se prende un led y se activa el rele
 * si se activa la palanca pasa lo mismo.
 */
 
 
//EDITABLE
#define SPRINT      true
#define NEED_REPOSO false
#define BOT0        4
#define BOT1        6
#define BOT2        8
#define BOT3        10
#define LUZ0        5
#define LUZ1        7
#define LUZ2        9
#define LUZ3        11
#define BUZZ        3
#define RELE        2

#define DS  50

const int N_INPUTS = 4;
const int INPUTS[N_INPUTS] = {BOT0,BOT1,BOT2,BOT3};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1,1};
const int N_OUTPUTS = 6;
const int OUTPUTS[N_OUTPUTS] = {LUZ0,LUZ1,LUZ2,LUZ3,BUZZ,RELE};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {0,0,0,0,0,0};

//random(0,3);
//NO EDITABLE
boolean nuevo = false;
boolean reposo = false;
boolean activo = false;
boolean resuelto = false;
unsigned long timer_print = 0;
////////////////////////////////////SETUP///////////////////////////////
//NO EDITABLE
const int TONOS[N_INPUTS] = {500,200,400,600};
const int LSECUENCIA = 9;
int SECUENCIA[LSECUENCIA] = {0,3,2,0,1,1,3,0,0};
boolean ret[N_INPUTS] = {0,0,0,0};
int actual = 0;
int binac = 0;
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

  int nac = num();
  bool rest = false;
  if(nac > -1){
    if(nuevo){nuevo = false;}else{
    if(binac + 1 == actual){
    if(nac == SECUENCIA[actual-1]){actual++;if(actual == LSECUENCIA){digitalWrite(RELE,1);  
    tone(BUZZ, 1000);
    reproduce();
    reproduce();
    reproduce();
    reproduce();
    reproduce();
    reproduce();
    reproduce();
    reproduce();
    reproduce();
    reproduce();
    reproduce();
    noTone(BUZZ);
    
    digitalWrite(RELE,0);actual = 0; binac = 0;}else{ SECUENCIA[actual] = random(0,3);reproduce();binac = 0;}}else{actual = 0;}
    }else{
      if(nac == SECUENCIA[binac]){binac++;}else{actual = 0;binac = 0;}}       
      }
  }}
}
void if_resuelto()
{
  if(resuelto){

  }
}

int num (){
  
      for(int a = 0;a < N_INPUTS;a++){ 
        if(check(0,INPUTS[a],DS)){
          if(actual == 0){
          Serial.println(a);
        //  tone(BUZZ, TONOS[a]);
          digitalWrite(OUTPUTS[0],HIGH);
          delay(500);
       //   noTone(BUZZ);
          digitalWrite(OUTPUTS[0],LOW);            
          digitalWrite(OUTPUTS[1],HIGH);
          delay(500);
       //   noTone(BUZZ);
          digitalWrite(OUTPUTS[1],LOW);  
          digitalWrite(OUTPUTS[2],HIGH);
          delay(500);
       //   noTone(BUZZ);
          digitalWrite(OUTPUTS[2],LOW);  
          digitalWrite(OUTPUTS[3],HIGH);
          delay(500);
       //   noTone(BUZZ);
          digitalWrite(OUTPUTS[3],LOW); 

          actual++;
          SECUENCIA[actual-1] = random(0,3);
          reproduce();
          nuevo = true;
            }else{
          Serial.println(a);
          tone(BUZZ, TONOS[a]);
          digitalWrite(OUTPUTS[a],HIGH);
          delay(500);
          noTone(BUZZ);
          digitalWrite(OUTPUTS[a],LOW);


          }
          return a;
    }}
  return -1;
  }

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    timer_print = millis();
    
    }
  }

void reproduce (){
  
  for(int i = 0; i < actual ; i++){
    
          tone(BUZZ, TONOS[SECUENCIA[i]]);
          digitalWrite(OUTPUTS[SECUENCIA[i]],HIGH);
          delay(500);
          noTone(BUZZ);
          digitalWrite(OUTPUTS[SECUENCIA[i]],LOW);
    
    
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
