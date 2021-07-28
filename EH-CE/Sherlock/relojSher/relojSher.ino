
/* Reloj
 * 
 * Arduino Nano, 1 sensor de puerta, 1 boton de reset
 * 
 * 
 * Sputnik Ar
 * 21/08/19
 */
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

//DEFINES
#define IMAN  3 
#define RESET 2

#define DS  50
  
const int pinCS = 10;
const int numberOfHorizontalDisplays = 4;
const int numberOfVerticalDisplays = 2;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

const int wait = 100; // En milisegundos
 
const int spacer = 1;
const int width = 6 + spacer; // Ancho de la fuente a 5 pixeles

//VARIABLES RELOJ
unsigned long contador = 0;
int HOR_FIN = 0;
int SEG_FIN = 0;
int MIN_FIN = 0;
int SEG_RES = 0;
int C_TIMER = 0;
unsigned int tiempo_restante = 3600;
unsigned long contador_tiempo = 0;
char toString[5] = {'T','6','0','0','0'};
boolean play = true;

void setup() {
  Serial.begin(9600);
  pinMode(IMAN,INPUT);
  pinMode(RESET,INPUT);
  pinMode(7,INPUT);
  pinMode(6,INPUT);
  pinMode(5,INPUT);
  digitalWrite(IMAN,1);
  digitalWrite(RESET,1);
 matrix.setIntensity(7); // Ajustar el brillo entre 0 y 15
 
 // Ajustar segun las necesidades
 matrix.setPosition(0, 0, 0); // El primer display esta en <0, 0>
 matrix.setPosition(1, 1, 0); // El segundo display esta en <1, 0>
 matrix.setPosition(2, 2, 0); // El tercer display esta en <2, 0>
 matrix.setPosition(3, 3, 0); // El cuarto display esta en <3, 0>
 matrix.setPosition(4, 4, 0); // El quinto display esta en <4, 0>
 matrix.setPosition(5, 5, 0); // El sexto display esta en <5, 0>
 matrix.setPosition(6, 6, 0); // El séptimo display esta en <6, 0>
 matrix.setPosition(7, 7, 0); // El octavo display esta en <7, 0>
 matrix.setPosition(8, 8, 0); // El noveno display esta en <8, 0>
 
 matrix.setRotation(0, 1); // Posición del display
 matrix.setRotation(1, 1); // Posición del display
 matrix.setRotation(2, 1); // Posición del display
 matrix.setRotation(3, 1); // Posición del display
 matrix.setRotation(4, 1); // Posición del display
 matrix.setRotation(5, 1); // Posición del display
 matrix.setRotation(6, 1); // Posición del display
 matrix.setRotation(7, 1); // Posición del display
 matrix.setRotation(8, 1); // Posición del display
 relojea();
}

void loop() {
 if(check(0,RESET,DS)){tiempo_restante = 3600;play=true;relojea();}
 relojea();
 controlea();


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
        matrix.write();
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
    while(probador >= 1){HOR_FIN++;probador--;}    
    probador = (SEG_RES - HOR_FIN * 3600) / 60;
    MIN_FIN = 0;     
    while(probador >= 1){MIN_FIN++;probador--;}
    SEG_FIN = SEG_RES - HOR_FIN * 3600 - MIN_FIN * 60;   
    int decenas = 0;
    int unidades = 0;
    
    if(HOR_FIN > 0){     
      decenas = HOR_FIN / 10;
      unidades = HOR_FIN - decenas * 10;
      matrix.drawChar(0, 0, decenas+48, HIGH, LOW, 1);
      matrix.drawChar(6, 0, unidades+48, HIGH, LOW, 1);
      matrix.drawChar(12, 0, ':', HIGH, LOW, 1);
      decenas = MIN_FIN / 10;
      unidades = MIN_FIN - decenas * 10;
      matrix.drawChar(18, 0, decenas+48, HIGH, LOW, 1);
      matrix.drawChar(24, 0, unidades+48, HIGH, LOW, 1);           
      }else{       
      decenas = MIN_FIN / 10;
      unidades = MIN_FIN - decenas * 10;
      matrix.drawChar(2, 4, decenas+48, HIGH, LOW, 1);
      matrix.drawChar(8, 4, unidades+48, HIGH, LOW, 1);
      matrix.drawChar(14, 4, ':', HIGH, LOW, 1);
      decenas = SEG_FIN / 10;
      unidades = SEG_FIN - decenas * 10;
      matrix.drawChar(20, 4, decenas+48, HIGH, LOW, 1);
      matrix.drawChar(26, 4, unidades+48, HIGH, LOW, 1);       
      
        }
    
    }
  
  }

void controlea()
{
  if(check(1,7,DS)){
    if(check(1,6,DS)){Serial.println('6');}
    if(check(1,5,DS)){Serial.println('5');} 
    Serial.println("Entre");
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
