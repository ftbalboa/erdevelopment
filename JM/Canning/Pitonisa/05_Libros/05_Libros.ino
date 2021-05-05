/*  LIBROS_05
 * 
 * MEGA, DFPLAYER, BOTONES Y RELES
 * 
 */
 
//EDITABLE
#define SPRINT      false
#define NEED_REPOSO true
#define LIBRO    25
#define BOTON    22
#define RELE1    24
#define RELE2    23

#define DS       30


const int N_INPUTS = 2;
const int INPUTS[N_INPUTS] = {LIBRO,BOTON};
const int INPUTS_ISTATE[N_INPUTS] = {1,1};
const int N_OUTPUTS = 2;
const int OUTPUTS[N_OUTPUTS] = {RELE1,RELE2};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,1};


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
        if(check(0,LIBRO,DS)){delay(100);if(check(0,LIBRO,DS)){digitalWrite(RELE1,LOW);reposo=false;activo=true;}}
  }
}

void if_activo()
{
  if(activo){
    if(check(0,BOTON,DS)){delay(100);if(check(0,BOTON,DS)){digitalWrite(RELE2,LOW);activo=false;resuelto=true;}}
  }
}

void if_resuelto()
{
  if(resuelto){
    digitalWrite(RELE1,LOW);
    digitalWrite(RELE2,LOW);
  }
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    Serial.print("Libro: ");
    Serial.println(check(0, LIBRO ,DS));
    Serial.print("Boton: ");
    Serial.println(check(0, BOTON ,DS));
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
