/* 04_NewPanel
 * 
 * MEGA, 6 BOTONES, 1 RELE, y 6 BI-LEDS
 * 
 */
 
 
//EDITABLE
#define SPRINT      true
#define NEED_REPOSO false
#define RELE  22
#define R4  2
#define G4  3
#define B4  4
#define R2  6
#define G2  7
#define B2  5
#define R3  8
#define G3  10
#define B3  9
#define R1  13
#define G1  11
#define B1  12

#define BOTO1    27
#define BOTO2    25
#define BOTO3    26
#define BOTO4    24


#define NCOLORES 4
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
const int INPUTS[N_INPUTS] = {BOTO1,BOTO2,BOTO3,BOTO4};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1,1};
const int N_OUTPUTS = 13;
const int OUTPUTS[N_OUTPUTS] = {RELE,R1,G1,B1,R2,G2,B2,R3,G3,B3,R4,G4,B4};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,0,0,0,0,0,0,0,0,0,0,0,0};


int actual1 = 0;
int actual2 = 0;
int actual3 = 0;
int actual4 = 0;


unsigned long timer1 = 0;
unsigned long timer2 = 0;
unsigned long timer3 = 0;
unsigned long timer4 = 0;


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
        digitalWrite(G1,HIGH);
        digitalWrite(B1,LOW);        
        break;}

      case 1:{
        digitalWrite(R1,LOW);
        digitalWrite(G1,HIGH);
        digitalWrite(B1,HIGH);
        break;} 

      case 2:{
        digitalWrite(R1,HIGH);
        digitalWrite(G1,HIGH);
        digitalWrite(B1,LOW);        
        break;}

      case 3:{
        digitalWrite(G1,HIGH);
        analogWrite(R1,125);
        analogWrite(B1,125);
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
        digitalWrite(G2,HIGH);
        digitalWrite(B2,LOW);        
        break;}

      case 1:{
        digitalWrite(R2,LOW);
        digitalWrite(G2,HIGH);
        digitalWrite(B2,HIGH);
        break;} 

      case 2:{
        digitalWrite(R2,HIGH);
        digitalWrite(G2,LOW);
        digitalWrite(B2,HIGH);        
        break;}

      case 3:{
        digitalWrite(R2,HIGH);
        analogWrite(G2,150);
        analogWrite(B2,125);
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
        digitalWrite(G3,HIGH);
        digitalWrite(B3,LOW);        
        break;}

      case 1:{
        digitalWrite(R3,LOW);
        digitalWrite(G3,HIGH);
        digitalWrite(B3,HIGH);
        break;} 

      case 2:{
        digitalWrite(R3,HIGH);
        digitalWrite(G3,LOW);
        digitalWrite(B3,HIGH);        
        break;}

      case 3:{
        digitalWrite(G3,HIGH);
        analogWrite(R3,125);
        analogWrite(B3,125);
        break;}   
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
        digitalWrite(R4,LOW);
        digitalWrite(G4,HIGH);
        digitalWrite(B4,HIGH);        
        break;}

      case 1:{
        digitalWrite(R4,HIGH);
        digitalWrite(G4,LOW);
        digitalWrite(B4,HIGH);
        break;} 

      case 2:{
        digitalWrite(R4,HIGH);
        digitalWrite(G4,HIGH);
        digitalWrite(B4,LOW);        
        break;}

      case 3:{
        digitalWrite(R4,HIGH);
        analogWrite(G4,125);
        analogWrite(B4,125);
        break;}   
    }
      if(check(0,BOTO4,DS)){  
      actual4++;  
      timer4 = millis();
      if(actual4 == NCOLORES){actual4 = 0;}
      }}

      
  if(actual1 == 3 && actual2 == 1 && actual3 == 2 && actual4 == 3 ){digitalWrite(RELE,LOW);}else{digitalWrite(RELE,HIGH);}
  }}


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
    Serial.println(actual1);
    Serial.println(actual2);
    Serial.println(actual3);
    Serial.println(actual4);

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
