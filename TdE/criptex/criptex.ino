/* Criptex
 * 
 * Arduino Nano, 4 reed switch, 1 rele
 * 1 piston
 * 
 * 
 * Sputnik Ar
 * 21/08/19
 */

//RESPUESTA

#define N_CABLES    4

const int SOLUCION[N_CABLES] = {3,1,4,2}; 
 
//EDITABLE
#define SPRINT      true
#define C1          2
#define C2          3
#define C3          4
#define C4          5

#define RELE        12
#define LED         13

#define DS  50

#define PIERDE_TIEMPO  2000

#define RETENCION  5000

const int N_INPUTS = 4;
const int INPUTS[N_INPUTS] = {C1,C2,C3,C4};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1,1};
const int N_OUTPUTS = 2;
const int OUTPUTS[N_OUTPUTS] = {RELE,LED};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,1};

int estado_cables[N_CABLES];

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


}

///////////////////////////////////////LOOP//////////////////////////////////////////
void loop() {
  barre();
  showme();
}

////////////////////////////////////////FUNCIONES///////////////////////////////////
//EDITABLE
void barre () //OUTPTS e INPUTS deben comenzar con los cables, sino agregar changui
{
    int correcto = 0;
    for(int j = 0; j < 4; j++){      
      if(check(0,INPUTS[j],DS)){correcto++;}
      }
      
    if(correcto == 4){digitalWrite(RELE,LOW);digitalWrite(LED,0);filtrado = millis();}else{
    
    if((millis() - filtrado) > RETENCION){digitalWrite(RELE,HIGH);digitalWrite(LED,1);}}  

}


void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    for(int i = 0; i < 4 ; i++){
      Serial.print("Sensor");
      Serial.print(i+1);
      Serial.print(": ");
      Serial.println(check(0,INPUTS[i],DS));}
    
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


