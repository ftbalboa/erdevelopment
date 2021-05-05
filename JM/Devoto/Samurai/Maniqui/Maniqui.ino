/* MANIQUI DEVOTO
 * 
 * NANO,BOTONES,DUINO CON COMU PULSATIL
 * 
 */
 
 
//EDITABLE
#define SPRINT      false
#define NEED_REPOSO false
#define BOTO1     2
#define BOTO2     3
#define BOTO3     4
#define BOTO4     5
#define OUT1      6
#define OUT2      7
#define OUT3      8
#define OUT4      9

#define PULSO 500


#define DS  1


const int N_INPUTS = 4;
const int INPUTS[N_INPUTS] = {BOTO1,BOTO2,BOTO3,BOTO4};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1,1};
const int N_OUTPUTS = 4;
const int OUTPUTS[N_OUTPUTS] = {OUT1,OUT2,OUT3,OUT4};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,1,1,1};


boolean actual1 = 0;
boolean actual2 = 0;
boolean actual3 = 0;
boolean actual4 = 0;

unsigned long contador_audio = 0;

unsigned long timer1 = 0;
unsigned long timer2 = 0;
unsigned long timer3 = 0;
unsigned long timer4 = 0;

boolean change1 = true;
boolean change2 = true;
boolean change3 = true;
boolean change4 = true;

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
    for(int i = 0;i < N_INPUTS;i++){
      if(check(0,INPUTS[i],DS)){
        
        switch(i){case 0:{timer1 = millis();digitalWrite(OUTPUTS[i],LOW);break;}
                  case 1:{timer2 = millis();digitalWrite(OUTPUTS[i],LOW);break;}
                  case 2:{timer3 = millis();digitalWrite(OUTPUTS[i],LOW);break;}
                  case 3:{timer4 = millis();digitalWrite(OUTPUTS[i],LOW);break;}}        
      }else{

        switch(i){case 0:{if(millis() - timer1 > PULSO){digitalWrite(OUTPUTS[i],HIGH);}break;}
                  case 1:{if(millis() - timer2 > PULSO){digitalWrite(OUTPUTS[i],HIGH);}break;}
                  case 2:{if(millis() - timer3 > PULSO){digitalWrite(OUTPUTS[i],HIGH);}break;}
                  case 3:{if(millis() - timer4 > PULSO){digitalWrite(OUTPUTS[i],HIGH);}break;} 
          
      }      
    }
  }
}
}
void if_resuelto()
{
  if(resuelto){
  }
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    Serial.print(timer1);Serial.print("    ");Serial.println(digitalRead(INPUTS[0]));
    Serial.print(timer2);Serial.print("    ");Serial.println(digitalRead(INPUTS[1]));
    Serial.print(timer3);Serial.print("    ");Serial.println(digitalRead(INPUTS[2]));
    Serial.print(timer4);Serial.print("    ");Serial.println(digitalRead(INPUTS[3]));
    timer_print = millis();
    
    }
  }

//NO EDITABLE
//comprueba el estado de un sensor
boolean check (boolean cual, int entrada, int ds)
{
  boolean resu = false;
  int contador = 0;  
  if(cual){ while(digitalRead(entrada) == 1 && resu == false){/*delay(ds);*/contador++;if(contador == ds){resu = true;}}
  }else{    while(digitalRead(entrada) == 0 && resu == false){/*delay(ds);*/contador++;if(contador == ds){resu = true;}}}  
  return resu; 
}
