/* PanelPuertaOcultaBunker
 * 
 * Arduino Nano, 8 canon, 1 rele
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
#define C5          6
#define C6          7
#define C7          8
#define C8          9
#define RELE        12
#define LED         13

#define DS  50

#define PIERDE_TIEMPO  2000

#define RETENCION  5000

const int N_INPUTS = 4;
const int INPUTS[N_INPUTS] = {C1,C2,C3,C4};
const int INPUTS_ISTATE[N_INPUTS] = {0,0,0,0};
const int N_OUTPUTS = 6;
const int OUTPUTS[N_OUTPUTS] = {C5,C6,C7,C8,RELE,LED};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {0,0,0,0,1,1};

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

//limpia estado cables
  for(int a = 0;a < N_CABLES;a++){ 
    estado_cables[a] = 0;
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
   boolean bool_cables[N_CABLES];
   for(int a = 0;a < N_CABLES;a++){ 
     bool_cables[a] = 0;
    }
  for(int i = 0; i < N_CABLES ; i++){
  
    for(int j = 0; j < N_CABLES; j++){
      if(i==j){
        digitalWrite(OUTPUTS[j],1);
      }else{
        digitalWrite(OUTPUTS[j],0); 
        }
      }
  
    for(int j = 0; j < PIERDE_TIEMPO; j++){}   //pierdeTiempo
    

    for(int j = 0; j < N_CABLES; j++){      
      if(check(1,INPUTS[j],DS)){estado_cables[j]=i+1;bool_cables[j] = true;}
      }
    
    }
  for(int a = 0;a < N_CABLES;a++){ 
     if(bool_cables[a] == 0){estado_cables[a]=0;}
    }  
}

void resuelve () //OUTPTS e INPUTS deben comenzar con los cables, sino agregar changui
{
  int correcto = 0;
  for(int i = 0; i < N_CABLES ; i++){
    if(SOLUCION[i] == estado_cables[i]){correcto++;}
    }
    
  if(correcto == N_CABLES){digitalWrite(RELE,LOW);digitalWrite(LED,0);filtrado = millis();}else{
    
    if((millis() - filtrado) > RETENCION){digitalWrite(RELE,HIGH);digitalWrite(LED,1);}}  
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    for(int i = 0; i < N_CABLES ; i++){
      Serial.print("CANON");
      Serial.print(i+1);
      Serial.print(": ");
      if(estado_cables[i]==0){Serial.println("desenchufado");}else{Serial.println(estado_cables[i]);}
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
