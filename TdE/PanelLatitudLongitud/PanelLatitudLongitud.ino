/* Panel Latitud Longitud
 * 
 * Arduino Nano, 4 reed switch, 1 rele
 * 1 piston
 * 
 * 
 * Sputnik Ar
 * 21/08/19
 */

//RESPUESTA
#define RPOTE1  0
#define RPOTE2  1024
#define RPOTE3  500
#define RPOTE4  700

#define POTE1    A1
#define POTE2    A2
#define POTE3    A3
#define POTE4    A4

#define CHANGUI    10

 
//EDITABLE
#define SPRINT      true

#define RELE        12
#define LED         13

#define DS  50

#define PIERDE_TIEMPO  2000

#define RETENCION  5000

const int N_OUTPUTS = 2;
const int OUTPUTS[N_OUTPUTS] = {RELE,LED};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,1};

//NO EDITABLE
unsigned long timer_print = 0;
unsigned long filtrado = 0;
////////////////////////////////////SETUP///////////////////////////////
//NO EDITABLE
void setup() {
  if(SPRINT){Serial.begin(9600);} 
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
    delay(DS);
    int pote1 = analogRead(POTE1);
    delay(DS);
    int pote2 = analogRead(POTE2);
    delay(DS);
    int pote3 = analogRead(POTE3);
    delay(DS);
    int pote4 = analogRead(POTE4);
    delay(DS);
    if((pote1 > (RPOTE1 + CHANGUI)) || (pote1 < (RPOTE1-CHANGUI))){}else{correcto++;}
    if((pote2 > (RPOTE2 + CHANGUI)) || (pote2 < (RPOTE2-CHANGUI))){}else{correcto++;}
    if((pote3 > (RPOTE3 + CHANGUI)) || (pote3 < (RPOTE3-CHANGUI))){}else{correcto++;}
    if((pote4 > (RPOTE4 + CHANGUI)) || (pote4 < (RPOTE4-CHANGUI))){}else{correcto++;}
      
    if(correcto == 4){digitalWrite(RELE,LOW);digitalWrite(LED,0);filtrado = millis();}else{
    
    if((millis() - filtrado) > RETENCION){digitalWrite(RELE,HIGH);digitalWrite(LED,1);}}  

}


void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    Serial.print("POTE1: ");
    Serial.println(analogRead(POTE1));
    delay(DS);
    Serial.print("POTE2: ");
    Serial.println(analogRead(POTE2));
    delay(DS);
    Serial.print("POTE3: ");
    Serial.println(analogRead(POTE3));
    delay(DS);
    Serial.print("POTE4: ");
    Serial.println(analogRead(POTE4));
    delay(DS);
    
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
