/* PadLuminoso
 * 
 * Arduino Nano, 9 botones con luz, 1 rele
 * 
 * 
 * Sputnik Ar
 * 24/08/19
 */

//RESPUESTA

#define N_BOTONES    9

const int SOLUCION[N_BOTONES] = { 1,0,0,
                                  0,1,1,
                                  0,1,0}; // Los que estan en 1 deben estar pulsados
#define SPRINT      true
#define BUT1          2
#define BUT2          3
#define BUT3          4
#define BUT4          5
#define BUT5          6
#define BUT6          7
#define BUT7          8
#define BUT8          9
#define BUT9          10
#define RELE        12
#define LED         13

#define DS  50

#define PIERDE_TIEMPO  2000

const int N_INPUTS = 9;
const int INPUTS[N_INPUTS] = {BUT7,BUT8,BUT9,BUT4,BUT5,BUT6,BUT1,BUT2,BUT3};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1,1,1,1,1,1,1};
const int N_OUTPUTS = 2;
const int OUTPUTS[N_OUTPUTS] = {RELE,LED};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,0};

boolean estado_botones[N_BOTONES];

//NO EDITABLE
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

//EDITABLE

//limpia estado cables
  for(int a = 0;a < N_BOTONES;a++){ 
    estado_botones[a] = 0;
  }

}

///////////////////////////////////////LOOP//////////////////////////////////////////
void loop() {
  barre();
  resuelve();
  showme();
}

////////////////////////////////////////FUNCIONES///////////////////////////////////
//EDITABLE
void barre () //OUTPTS e INPUTS deben comenzar con los cables, sino agregar changui
{
  for(int a = 0; a < N_BOTONES; a++) {
    estado_botones[a] = check(1,INPUTS[a],DS);
    } 
}

void resuelve () //OUTPTS e INPUTS deben comenzar con los cables, sino agregar changui
{
  int correcto = 0;
  for(int i = 0; i < N_BOTONES ; i++){
    if(SOLUCION[i] == estado_botones[i]){correcto++;}
    }
  if(correcto == N_BOTONES){digitalWrite(RELE,LOW);digitalWrite(LED,0);}else{digitalWrite(RELE,HIGH);digitalWrite(LED,1);}  
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    for(int i = 0; i < N_BOTONES ; i++){
      Serial.print(estado_botones[i]);
      Serial.print(",");
      if(i == 2 || i== 5 || i == 8){Serial.println();}
      }
 
    if(digitalRead(RELE)){Serial.println("Sin resolver");}else{Serial.println("Resuelto");}
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
