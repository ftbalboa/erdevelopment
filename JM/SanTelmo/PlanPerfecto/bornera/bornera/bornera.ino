//DEFINES
#define SENSORES_NUM  25
#define SALIDA  50
#define INICIO_SENSORES 20
#define DS 10
//GLOBALES
boolean sensores_act[SENSORES_NUM];
int SENSORES_POS[SENSORES_NUM];
const boolean SOLUCION[SENSORES_NUM]={0,0,0,0,0,
                                      0,0,0,0,0,
                                      0,0,0,0,0,
                                      0,0,0,0,0,
                                      0,0,0,0,0};
void setup() {
  pinMode(SALIDA,OUTPUT);
  int a = 0;
  while(a < SENSORES_NUM){pinMode(INICIO_SENSORES+a,INPUT);a++;}
}

void loop() {
  sensorea();
  if(comparea()){digitalWrite(SALIDA,HIGH);}else{digitalWrite(SALIDA,LOW);};
}

//comprueba el estado de un sensor
boolean check (boolean cual, int entrada, int ds)
{
  boolean resu = false;  
  if(cual){ if(digitalRead(entrada) == 1){delay(ds);if(digitalRead(entrada)==1){resu = true;}}
  }else{    if(digitalRead(entrada) == 0){delay(ds);if(digitalRead(entrada)==0){resu = true;}}}  
  return resu; 
}
//comprueba el estado de todos los sensores, utiliza check
void sensorea()
{
  int a = 0;
  while(a < SENSORES_NUM){
  sensores_act[a] = check(true , SENSORES_POS[a] , DS);
  a++;
  }
}

boolean comparea()
{
  int a = 0;
  boolean loopea = true;
  while(loopea){
    if(sensores_act[a]==SOLUCION[a]){a++;}else{loopea=false;return false;}
    if(a = SENSORES_NUM){loopea = true;} 
    }
  return true;
}



