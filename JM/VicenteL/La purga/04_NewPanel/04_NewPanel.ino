/* 04_NewPanel
 * 
 * MEGA, 6 BOTONES, 1 RELE, y 6 BI-LEDS
 * 
 */
 
 
//EDITABLE
#define SPRINT      false
#define NEED_REPOSO false
#define RELE  40
#define R1  22
#define G1  23
#define R2  24
#define G2  25
#define R3  26
#define G3  27
#define R4  28
#define G4  29
#define R5  30
#define G5  31
#define R6  32
#define G6  33
#define BOTO1    34
#define BOTO2    35
#define BOTO3    36
#define BOTO4    37
#define BOTO5    38
#define BOTO6    39

#define NCOLORES 2
#define DS  10
#define RES_AMP1 230
#define RES_AMP2 50
#define RES_AMP3 170
#define CHANGUI 20
#define LIM_AMP1 255
#define LIM_AMP2 255
#define LIM_AMP3 210

#define VELOCIDAD 10

#define RETENCION 500

const int N_INPUTS = 6;
const int INPUTS[N_INPUTS] = {BOTO1,BOTO2,BOTO3,BOTO4,BOTO5,BOTO6};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1,1,1,1};
const int N_OUTPUTS = 13;
const int OUTPUTS[N_OUTPUTS] = {RELE,R1,G1,R2,G2,R3,G3,R4,G4,R5,G5,R6,G6};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,0,0,0,0,0,0,0,0,0,0,0,0};


int actual1 = 0;
int actual2 = 0;
int actual3 = 0;
int actual4 = 0;
int actual5 = 0;
int actual6 = 0;

unsigned long timer1 = 0;
unsigned long timer2 = 0;
unsigned long timer3 = 0;
unsigned long timer4 = 0;
unsigned long timer5 = 0;
unsigned long timer6 = 0;

unsigned long contador_audio = 0;


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
/////////////////////1////////////////////////
  if(millis() - timer1 > RETENCION){
    switch(actual1){
      
      case 0:{
        digitalWrite(R1,HIGH);
        digitalWrite(G1,LOW);
        break;}

      case 1:{
        digitalWrite(R1,LOW);
        digitalWrite(G1,HIGH);
        break;}           
        }
      if(check(0,BOTO1,DS)){  
      actual1++;
      timer1 = millis();  
      if(actual1 == NCOLORES){actual1 = 0;}
      }}
/////////////2//////////////////////////
  if(millis() - timer2 > RETENCION){
    switch(actual2){
      
      case 0:{
        digitalWrite(R2,HIGH);
        digitalWrite(G2,LOW);
        break;}

      case 1:{
        digitalWrite(R2,LOW);
        digitalWrite(G2,HIGH);
        break;} 
                
        }
      if(check(0,BOTO2,DS)){  
      actual2++; 
      timer2 = millis(); 
      if(actual2 == NCOLORES){actual2 = 0;}
      }}
//////////////////////////3///////////////////////////
  if(millis() - timer3 > RETENCION){
    switch(actual3){
      
      case 0:{
        digitalWrite(R3,HIGH);
        digitalWrite(G3,LOW);
        break;}

      case 1:{
        digitalWrite(R3,LOW);
        digitalWrite(G3,HIGH);
        break;}              
        }
      }
      if(check(0,BOTO3,DS)){  
      actual3++;  
      timer3 = millis();
      if(actual3 == NCOLORES){actual3 = 0;}
      }}
/////////////////////////4///////////////////////////
  if(millis() - timer4 > RETENCION){
    switch(actual4){
      
      case 0:{
        digitalWrite(R4,HIGH);
        digitalWrite(G4,LOW);
        break;}

      case 1:{
        digitalWrite(R4,LOW);
        digitalWrite(G4,HIGH);
        break;} 
    }
      if(check(0,BOTO4,DS)){  
      actual4++;  
      timer4 = millis();
      if(actual4 == NCOLORES){actual4 = 0;}
      }}
/////////////////////////5///////////////////////////
  if(millis() - timer5 > RETENCION){
    switch(actual5){
      
      case 0:{
        digitalWrite(R5,HIGH);
        digitalWrite(G5,LOW);
        break;}

      case 1:{
        digitalWrite(R5,LOW);
        digitalWrite(G5,HIGH);
        break;} 
    }
      if(check(0,BOTO5,DS)){  
      actual5++;  
      timer5 = millis();
      if(actual5 == NCOLORES){actual5 = 0;}
      }}
/////////////////////////6///////////////////////////
  if(millis() - timer6 > RETENCION){
    switch(actual6){
      
      case 0:{
        digitalWrite(R6,HIGH);
        digitalWrite(G6,LOW);
        break;}

      case 1:{
        digitalWrite(R6,LOW);
        digitalWrite(G6,HIGH);
        break;} 
    }
      if(check(0,BOTO6,DS)){  
      actual6++; 
      timer6 = millis(); 
      if(actual6 == NCOLORES){actual6 = 0;}
      }}
      
  if(actual1 == 0 && actual2 == 1 && actual3 == 1 && actual4 == 0 && actual5 == 0 && actual6 == 1 ){digitalWrite(RELE,LOW);}else{digitalWrite(RELE,HIGH);}
  }


void if_resuelto()
{
  if(resuelto){
    digitalWrite(RELE, LOW);
  }
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    Serial.print("R1: ");

    }
  }


//NO EDITABLE
//comprueba el estado de un sensor
boolean check (boolean cual, int entrada, int ds)
{
  boolean resu = false;
  int contador = 0;  
  if(cual){ while(digitalRead(entrada) == 1 && resu == false){delay(ds);contador++;if(contador == 5){resu = true;}}
  }else{    while(digitalRead(entrada) == 0 && resu == false){delay(ds);contador++;if(contador == 5){resu = true;}}}  
  return resu; 
}
