/* Reloj
 * 
 * Arduino Nano, 1 sensor de puerta, 1 boton de reset
 * 
 * 
 * Sputnik Ar
 * 21/08/19
 */

//INCLUDES
#include <TM1637.h>
// Instantiation and pins configurations
// Pin 2 - > DIO
// Pin 3 - > CLK
TM1637 tm1637(10, 11);

//DEFINES 
#define RESET 4

#define DS  50
  


//VARIABLES RELOJ
unsigned long contador = 0;
int HOR_FIN = 0;
int SEG_FIN = 0;
int MIN_FIN = 0;
int SEG_RES = 0;
int C_TIMER = 0;
unsigned int tiempo_restante = 1800;
unsigned long contador_tiempo = 0;
char toString[5] = {'T','6','0','0','0'};
boolean play = true;

void setup() {
  delay(1000);
  Serial.begin(9600);
  pinMode(RESET,INPUT);
  digitalWrite(RESET,1);
  tm1637.init();
  tm1637.setBrightness(5);
  tm1637.switchColon();
}

void loop() {
 relojea();
}


void relojea()
{
  if(play){
    if ((millis() - contador_tiempo) >= 1000) {        //
      contador_tiempo = millis();
      Serial.println(tiempo_restante);
      if(tiempo_restante != 0){
        tiempo_restante = tiempo_restante - 1;
        actualiza();

      }
    }  
  }
}
  


void actualiza(){

  SEG_RES = tiempo_restante; /*- segundos*/;

  if(SEG_RES >= 0){
    int probador = 0;
    probador = SEG_RES / 3600;
    HOR_FIN = 0;        
    probador = (SEG_RES - HOR_FIN * 3600) / 60;
    MIN_FIN = 0;     
    while(probador >= 1){MIN_FIN++;probador--;}
    SEG_FIN = SEG_RES - HOR_FIN * 3600 - MIN_FIN * 60;   
    int decenas = 0;
    int unidades = 0;
    
     
      decenas = MIN_FIN / 10;
      unidades = MIN_FIN - decenas * 10;

      decenas = SEG_FIN / 10;
      unidades = SEG_FIN - decenas * 10;
      tm1637.dispNumber(SEG_FIN+ MIN_FIN*100);    
      
        
    
    }
  
  }

boolean check (boolean cual, int entrada, int ds)
{
  boolean resu = false;
  int contador = 0;  
  if(cual){ while(digitalRead(entrada) == 1 && resu == false){contador++;if(contador == ds){resu = true;}}
  }else{    while(digitalRead(entrada) == 0 && resu == false){contador++;if(contador == ds){resu = true;}}}  
  return resu; 
}
