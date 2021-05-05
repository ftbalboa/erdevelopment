/* ROMPECABEZAS_Y_DIOSES_07
 * 
 * MEGA, SENSORES DE VENTANA, RELES, OPTOS
 * 
 */
 
//EDITABLE
#define SPRINT      false
#define NEED_REPOSO false
#define ROMPE    26
#define DIOSE    27
#define RELER    22
#define RELED    23
#define OPTOR    24
#define OPTOD    25

#define DS       30


const int N_INPUTS = 2;
const int INPUTS[N_INPUTS] = {ROMPE,DIOSE};
const int INPUTS_ISTATE[N_INPUTS] = {1,1};
const int N_OUTPUTS = 4;
const int OUTPUTS[N_OUTPUTS] = {RELER,RELED,OPTOR,OPTOD};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,1,0,0};

boolean vdios = true;
boolean vromp = true;

//OBJETOS

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
    if(check(0,ROMPE,DS)){if(check(0,ROMPE,DS)){digitalWrite(RELER,LOW);if(vromp){vromp=false;digitalWrite(OPTOR,HIGH);delay(5000);digitalWrite(OPTOR,LOW);}}}
    if(check(0,DIOSE,DS)){if(check(0,DIOSE,DS)){if(vdios){vdios=false;digitalWrite(OPTOD,HIGH);delay(5000);digitalWrite(OPTOD,LOW);delay(15000);digitalWrite(RELED,LOW);}}}
  }
}

void if_resuelto()
{
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    Serial.print("Rompe: ");
    Serial.println(check(0, ROMPE ,DS));
    Serial.print("Dioses: ");
    Serial.println(check(0, DIOSE ,DS));
    timer_print = millis();
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
