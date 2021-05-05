/* Telefono
 * 
 * Arduino Nano, 1xdisco de telefono, 2xpiston
 * 
 * 
 * Sputnik Ar
 * 24/08/19
 */

//RESPUESTA

#define NUMEROS    8
//RESPUESTA

const int TELEFONO[NUMEROS] = { 1,2,3,4,9,8,7,0}; // Poner numero deseado


#define SPRINT      true
#define START          3
#define NUM            2


#define RELE        12
#define LED         13

#define DS  500

#define PIERDE_TIEMPO  2000

#define RETENCION  2000

const int N_INPUTS = 2;
const int INPUTS[N_INPUTS] = {START,NUM};
const int INPUTS_ISTATE[N_INPUTS] = {1,1};
const int N_OUTPUTS = 2;
const int OUTPUTS[N_OUTPUTS] = {RELE,LED};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,0};


//NO EDITABLE
unsigned long timer_print = 0;
unsigned long filtrado = 0;
int ingreso[NUMEROS]{};
int posicion = 0;

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
  int numero= -1;
  boolean discando = true;
  while(check(1,START,DS)){
    if(discando){discando = false;{Serial.print("Discando: ");}}
    boolean nuevo = false;
    while(check(0, NUM, DS)){nuevo = true;}
    if(nuevo){numero++;Serial.print(" . ");}  
    }
   if(numero != -1){
    if(numero == 9){numero = -1;}
    numero++; 
    Serial.println(numero);    
   if(digitalRead(RELE) == LOW){ if(numero == 0){posicion = 0; Serial.println("Ordenado ");digitalWrite(RELE,1);digitalWrite(LED,0);}}else{
    if(numero == TELEFONO[posicion]){Serial.print("Numero ");Serial.print(posicion+1);Serial.println(" correcto");posicion++;}else{posicion = 0;}
    if(posicion == NUMEROS){    
      digitalWrite(RELE,LOW);
      digitalWrite(LED,1);
      Serial.println("Resuelto");}
   }
}}

////////////////////////////////////////FUNCIONES///////////////////////////////////
//EDITABLE



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
