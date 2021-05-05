/* PadDeExpedicion
 * 
 * Arduino Nano, 4botones con luz, 1 pote, 1 rele, 1 LUZ220V
 * 
 * 
 * Sputnik Ar
 * 24/08/19
 */

//RESPUESTA

#define N_BOTONES    4
//RESPUESTA
#define RPOTE1  0
const boolean SOLUCION[N_BOTONES] = { 1,0,1,0}; // Los que estan en 1 deben estar pulsados

#define POTE1    A0
#define CHANGUI    10

#define SPRINT      true
#define BUT1          8
#define BUT2          9
#define BUT3          10
#define BUT4          7

#define RELE        12
#define LED         13

#define DS  50

#define PIERDE_TIEMPO  2000

#define RETENCION  2000

const int N_INPUTS = 4;
const int INPUTS[N_INPUTS] = {BUT1,BUT2,BUT3,BUT4};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1,1};
const int N_OUTPUTS = 2;
const int OUTPUTS[N_OUTPUTS] = {RELE,LED};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,1};

boolean estado_botones[N_BOTONES];

//NO EDITABLE
unsigned long timer_print = 0;
unsigned long filtrado = 0;
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
  int pote1 = analogRead(POTE1);
  if((pote1 - CHANGUI) > RPOTE1 || (pote1+CHANGUI) < RPOTE1){}else{correcto++;}
  
    if(correcto == 5){digitalWrite(RELE,LOW);digitalWrite(LED,0);filtrado = millis();}else{
    
    if((millis() - filtrado) > RETENCION){digitalWrite(RELE,HIGH);digitalWrite(LED,1);}}  
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    for(int i = 0; i < N_BOTONES ; i++){
      Serial.print(estado_botones[i]);
      Serial.print(",");
      if(i == 3 || i== 5 || i == 8){Serial.println();}
      }
    Serial.print("POTE1: ");
    Serial.println(analogRead(POTE1));
 
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
