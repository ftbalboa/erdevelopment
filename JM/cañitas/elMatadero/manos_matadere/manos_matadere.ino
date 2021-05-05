/* Base Sputnik Slave
 *  
 *  
 *  
 *  
 *  
 * 3/02/2020 
 */


//DEFINES
#define SPRINT      true
#define NEED_REPOSO true

#define NLED        4

#define A           2
#define TX          3
#define OUT         4
#define R           7
#define A           2
#define M1          9
#define M2          6
#define M3          5
//#define R1          A0
//#define R2          A1

#define BINC          8
#define B0T1           10
#define B0T2           11
#define B0T3           12
#define B0T4           A0
#define B0T5           A1

#define NCOLORES    6

#define DS  200

#define TIEMPO_LETRA    1000

//CONSTANTES
const int N_INPUTS = 8;
const int INPUTS[N_INPUTS] = {R , A, BINC, B0T1,B0T2,B0T3,B0T4,B0T5};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1,1,1,1,1,1};
const int N_OUTPUTS = 3;
const int OUTPUTS[N_OUTPUTS] = {M1,M2,OUT};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,0,0};


//VARIABLES
unsigned long contador_tiempo = 0;
const int NR = 5;
const int RESPUESTA[NR] = {1,5,2,3,4};
unsigned long luzcount = 0;

int correcta = 0;

int apriete = -1;

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
    if(check(0, R, DS)){reposo = false; activo = true;}
  }
}

void if_activo()
{
  if(activo){
    int bact = -1;
    for(int i = 0;i < 6 ; i++){
      if(check(0, INPUTS[i+2],DS)){bact = i;
      i = 6;
      digitalWrite(M2,HIGH);
      luzcount = millis();  
      }}
    if(millis() - luzcount > 1000){digitalWrite(M2, LOW);}

      if(bact > -1 && apriete != bact ){
        apriete = bact;      
        Serial.print("Boton: "); Serial.println(bact); 
        Serial.print("secuencia: "); Serial.println(correcta);
        if(bact == RESPUESTA[correcta]){correcta++;}else{correcta = 0;}

      }

      if(correcta == NR || check(0, A, DS)){reposo = false; activo = false; resuelto = true;}   

      



  }
}

void if_resuelto()
{
  if(resuelto){
    digitalWrite(M1, LOW);
    digitalWrite(OUT, HIGH);
    if(check(1, R, DS) && check(0, A, DS)){reset();}
  }
}

void reset(){
  
    if(NEED_REPOSO){reposo=true;activo=false;resuelto=false;}else{reposo=false;activo=true;resuelto=false;}
  //declara entradas
  for(int a = 0;a < N_INPUTS;a++){ 
    pinMode(INPUTS[a] , INPUT);
    digitalWrite(INPUTS[a] , INPUTS_ISTATE[a]);
  }
//declara salidas
  for(int a = 0;a < N_OUTPUTS;a++){ 
    pinMode(OUTPUTS[a] , OUTPUT);
    digitalWrite(OUTPUTS[a] , OUTPUTS_ISTATE[a]);}

    correcta = 0;
    apriete = -1;
  }

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");

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
