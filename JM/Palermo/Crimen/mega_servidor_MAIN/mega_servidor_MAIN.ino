/************************************
* CRIMEN-SERVIDOR-MAIN              *
* ---------------------------       *
* ARDUINO MEGA - 2 DFPLAYER, 3 UNO, *             
* 3 REED SWITCH, 1 ENFORCER,        *                          
* 8 PALANCAS MATRICIALES, PIXEL LED *
* 8 RELES                           *
* ---------------------------       *
* Controla la sala comunicandose por*
* I2C con 3 UNOS                    *
*                                   *
* ----------------------------------*
* V1.01 9/02/2018                   *
*************************************/

//INCLUDES
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "FastLED.h"
#include <Wire.h>

//DEFINES

//FASTLED

#define NUM_LEDS 7
#define DATA_PIN 12
#define CLOCK_PIN 13
CRGB leds[NUM_LEDS];

//DECLARACIONES LIB.MP3

 /******AUDIOS DFP1******
  1-FUNCIONAL 
  2-RELOJ
  3-CHIMENEA
  4-BAUL
  5-TELEFONO
  6-APLAUSO  
  ******************/

 /******AUDIOS DFP2******
  SITUACIONAL
  ******************/  

SoftwareSerial mySoftwareSerial(3, 2); // RX, TX
//SoftwareSerial mySoftwareSerial2(4, 5); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
//DFRobotDFPlayerMini myDFPlayer2;
void printDetail(uint8_t type, int value);  

/******************************************
 * I2C                                    *
 * SLAVES 1,2,3                           *
 * LEER Y o N (resuelto si o no)          *
 * ESCRIBIR A o D (activate o desactivate)*
 ******************************************/

//BOTONERA
#define COLUMNA1 41
#define COLUMNA2 40
#define COLUMNA3 43
#define FILA1 42
#define FILA2 45
#define FILA3 44

//RELES
#define R_RELOJ     46
#define R_CHIMENEA  47
#define R_CAJON1    48
#define R_CAJON2    49
#define R_PFINAL    50
#define R_LUZ       51
#define R_AUDIO     52
#define R_SITUACION 53

//SENSORES
#define S_LIBROS    A7  //Analogico
#define S_RELOJ     38
#define S_ENFORCER  37
#define S_PFINAL    36

#define dp 50       //delay anti-ruido palancas
#define delay_s 50

boolean palanca[8] = {false , false , false , false , false , false , false , false};

int ordenar = 0;
#define C_PASOS 7
int paso = 0;

boolean play = false;
boolean pause = false;

void setup() {

  //LEDS
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  //I2C
  Wire.begin();
  //botonera
  pinMode(COLUMNA1 , OUTPUT);
  pinMode(COLUMNA2 , OUTPUT);
  pinMode(COLUMNA3 , OUTPUT);
  pinMode(FILA1 , INPUT);
  digitalWrite(FILA1 , HIGH);
  pinMode(FILA2 , INPUT);
  digitalWrite(FILA2 , HIGH);
  pinMode(FILA3 , INPUT);
  digitalWrite(FILA3 , HIGH);
  //reles
  pinMode(R_RELOJ,OUTPUT);
  digitalWrite(R_RELOJ,HIGH);
  pinMode(R_CHIMENEA,OUTPUT);
  digitalWrite(R_CHIMENEA,HIGH);
  pinMode(R_CAJON1,OUTPUT);
  digitalWrite(R_CAJON1,HIGH);
  pinMode(R_CAJON2,OUTPUT);
  digitalWrite(R_CAJON2,HIGH);
  pinMode(R_PFINAL,OUTPUT);
  digitalWrite(R_PFINAL,HIGH);
  pinMode(R_LUZ,OUTPUT);
  pinMode(R_AUDIO,OUTPUT);
  pinMode(R_SITUACION,OUTPUT);  
  //sensores
  pinMode(S_RELOJ, INPUT);
  digitalWrite(S_RELOJ, HIGH);
  pinMode(S_ENFORCER, INPUT);
  digitalWrite(S_ENFORCER, HIGH);
  pinMode(S_PFINAL, INPUT);
  digitalWrite(S_PFINAL, HIGH);
    
  Serial.begin(9600);
delay(1000);
  mySoftwareSerial.begin(9600);
  Serial.println("INICIANDO");
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    Serial.println(myDFPlayer.readState()); //read mp3 state
    Serial.println(myDFPlayer.readFileCounts()); //read all file counts in SD card
    //myDFPlayer.play(11); //AUDIO DE CONFIRMACION PORQUE CRASHEA
  }
  Serial.println("INICIO AUDIO");  
  full(7,0,5,0);
  FastLED.show();
  myDFPlayer.volume(12);

}

void loop() {

  detect_boton(palanca);

  if(palanca[7] == 0){pause = true; play = false;}else{pause = false; play = true;}

  secuencia(play);

  orden(pause);

  mostrar (); //muestra por puerto serie estados de cosas

}

void detect_boton(boolean palancas[8]){
  
  digitalWrite(COLUMNA1 , LOW);
  delay(50);
  if(digitalRead(FILA1)){delay(dp);if(digitalRead(FILA1)){palancas[0]=true;}else{palancas[0]=false;}}else{palancas[0]=false;}
  if(digitalRead(FILA2)){delay(dp);if(digitalRead(FILA2)){palancas[2]=true;}else{palancas[2]=false;}}else{palancas[2]=false;}
  if(digitalRead(FILA3)){delay(dp);if(digitalRead(FILA3)){palancas[7]=true;}else{palancas[7]=false;}}else{palancas[7]=false;}

  digitalWrite(COLUMNA1 , HIGH);
  digitalWrite(COLUMNA2 , LOW);
  delay(50);
  if(digitalRead(FILA1)){delay(dp);if(digitalRead(FILA1)){palancas[6]=true;}else{palancas[6]=false;}}else{palancas[6]=false;}
  if(digitalRead(FILA2)){delay(dp);if(digitalRead(FILA2)){palancas[1]=true;}else{palancas[1]=false;}}else{palancas[1]=false;}
  if(digitalRead(FILA3)){delay(dp);if(digitalRead(FILA3)){palancas[5]=true;}else{palancas[5]=false;}}else{palancas[5]=false;}

  digitalWrite(COLUMNA2 , HIGH);
  digitalWrite(COLUMNA3 , LOW);
  delay(50);
  if(digitalRead(FILA1)){delay(dp);if(digitalRead(FILA1)){palancas[4]=true;}else{palancas[4]=false;}}else{palancas[4]=false;}
  if(digitalRead(FILA2)){delay(dp);if(digitalRead(FILA2)){palancas[3]=true;}else{palancas[3]=false;}}else{palancas[3]=false;}
  

  digitalWrite(COLUMNA3 , HIGH);
  
  }

  void color (int led , int col , int tiempo , boolean imprimir) {
  
  switch (col){

    case 0 : 

      leds[led] = CRGB ::Black;

      break;
    
    case 1 :

      leds[led] = CRGB ::Black;

      break;

    case 2 :

      leds[led] = CRGB ::DarkOrange;

    break;

    case 3 :

      leds[led] = CRGB ::White;

      break;

        case 4 :

      leds[led] = CRGB ::Red;

      break;

        case 5 :

      leds[led] = CRGB ::Yellow;

      break;
    
    case 6 :

      leds[led] = CRGB ::Green;

      break;
  
   case 7 :

      leds[led] = CRGB ::Blue;
      
      break;
    
    
    
    }


    if(col != 0 && col != 1 && imprimir){  FastLED.show();delay(tiempo);}
  
  

  }

void full (int cantidad , int led_inicio , int col , int tiempo){
  
  boolean imprimir = true;
  
    int  c = 0;

  if (tiempo == 0){imprimir = false;}

  while(c < (cantidad)) {

    color(led_inicio + c , col, tiempo, imprimir);
    
    c++;

    
    }
  
  if(tiempo == 0){FastLED.show();}
  
  }


void mostrar (){

Serial.println("PALANCAS");
Serial.print(palanca[0]);
Serial.print(palanca[1]);
Serial.print(palanca[2]);
Serial.print(palanca[3]);
Serial.print(palanca[4]);
Serial.print(palanca[5]);
Serial.print(palanca[6]);
Serial.println(palanca[7]);
Serial.println("FILAS");
Serial.print(digitalRead(FILA1));
Serial.print(digitalRead(FILA2));
Serial.println(digitalRead(FILA3));
Serial.println("COLUMNAS");
Serial.print(digitalRead(COLUMNA1));
Serial.print(digitalRead(COLUMNA2));
Serial.println(digitalRead(COLUMNA3));
Serial.print("RELOJ ");
Serial.println(digitalRead(S_RELOJ)); 
  }

boolean I2C_read (int slave){

  boolean estado = false;
  
  Wire.requestFrom(slave, 1);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    if(c == 'Y'){estado = true;}else{estado = false;}         // print the character

    Serial.println(slave);
    Serial.println(c);
  } 
  
  return estado; 
 }  

void I2C_write (int slave, boolean activate, boolean ordenate){
  
  Wire.beginTransmission(slave); // transmit to device #8
  if(ordenate){Wire.write('K');Serial.println(slave);Serial.println('K');}else{
  if(activate){Wire.write('A');}else{Wire.write('D');}}             // sends one byte
  Wire.endTransmission();    // stop transmitting
  
  }

void secuencia (boolean on){
  
  if(on){
    
    switch(paso){
      
      case 0:
        if(check(false , S_PFINAL , delay_s)){activadores(paso); paso++;}
      break;

      case 1:
        if(analogRead(S_LIBROS) < 500 || palanca[paso-1] == 0){activadores(paso); paso++;}
      break;
      
      case 2:
        if(check(false , S_RELOJ , delay_s) || palanca[paso-1] == 0){activadores(paso); paso++;}
      break;      

      case 3:
        if(check(false , S_ENFORCER , delay_s)|| palanca[paso-1] == 0){activadores(paso); paso++;}
      break;

      case 4:
        if(I2C_read(1) || palanca[paso-1] == 0){activadores(paso); paso++;}
      break;

      case 5:
        if(I2C_read(2) || palanca[paso-1] == 0){activadores(paso); paso++;}
      break;

      case 6:
        if(I2C_read(3) || palanca[paso-1] == 0){activadores(paso); paso++;}
      break;

      case 7:
        if(palanca[paso-1] == 0){activadores(paso); paso++;}
      break;
      }
    
    
    
    }
  
  
  
  
  
  
  }

void activadores (int paso){
  
  switch(paso){
      
      case 0:
      
       digitalWrite(R_PFINAL , HIGH);
       full(7,0,6,0);
       FastLED.show();
       myDFPlayer.play(1);
       
      break;

      case 1:
      
       digitalWrite(R_RELOJ , LOW);
       //myDFPlayer.volume(30);
       myDFPlayer.play(2);
       color(paso-1 , 4 , 0 , true);
       delay(2000);
       //myDFPlayer.volume(15);
       myDFPlayer.play(1);
       
      break;
      
      case 2:
      
       digitalWrite(R_CHIMENEA , LOW);
       //myDFPlayer.volume(20);
       myDFPlayer.play(3);
       color(paso-1 , 4 , 0 , true);
       delay(2000);
       //myDFPlayer.volume(15);
       myDFPlayer.play(1);
       
      break;      

      case 3:
       digitalWrite(R_CAJON1 , LOW);
       //myDFPlayer.play(4);
       color(paso-1 , 4 , 0 , true);
       //delay(2000);
       //myDFPlayer.play(1);
       I2C_write(1 ,false , true);
      break;

      case 4:
       digitalWrite(R_CAJON2 , LOW);
      // myDFPlayer.volume(20);
       myDFPlayer.play(4);
       color(paso-1 , 4 , 0 , true);
       delay(2000);
       //myDFPlayer.volume(15);
       myDFPlayer.play(1);
      break;

      case 5:
       digitalWrite(R_LUZ , HIGH);
      // myDFPlayer.volume(25);
       myDFPlayer.play(5);
       I2C_write(3 ,true , false);
       color(paso-1 , 4 , 0 , true);
       delay(500);
       //myDFPlayer.volume(15);
       myDFPlayer.play(1);
      break;

      case 6:
       digitalWrite(R_AUDIO , HIGH);
       color(paso-1 , 4 , 0 , true);
      break;

      case 7:
       I2C_write(3 ,false , true);
       //myDFPlayer.volume(30);
       myDFPlayer.play(6);
       delay(6000);
       digitalWrite(R_PFINAL , LOW);
       digitalWrite(R_AUDIO , LOW);
       color(paso-1 , 4 , 0 , true);
      break;
      }
  
  
  
  
  
  
  }

void orden (boolean on){
  
  if(on){
    

  
  switch(ordenar){
      

      case 0:
      if(analogRead(S_LIBROS) > 500){color(ordenar , 7 , 0 , false);}else{color(ordenar , 0 , 0 , false);}
      reset();
      break;
      
      case 1:
      if(check(true , S_RELOJ , delay_s)){color(ordenar , 7 , 0 , false);}else{color(ordenar , 0 , 0 , false);}
      break;      

      case 2:
      if(check(true , S_ENFORCER , delay_s)){color(ordenar , 7 , 0 , false);}else{color(ordenar , 0 , 0 , false);}
      I2C_write(1 ,false , true);
      break;

      case 3:
      if(I2C_read(1) == 0){color(ordenar , 7 , 0 , false);}else{color(ordenar , 0 , 0 , false);}
      break;

      case 4:
      if(I2C_read(2) == 0){color(ordenar , 7 , 0 , false);}else{color(ordenar , 0 , 0 , false);}
      break;

      case 5:
      if(I2C_read(3) == 0){color(ordenar , 7 , 0 , false);}else{color(ordenar , 0 , 0 , false);}
      break;

      case 6:
      if(palanca[6] == 1){color(ordenar , 7 , 0 , false);}else{color(ordenar , 0 , 0 , false);}
      break;
      }
    FastLED.show();
    ordenar++;

    if(ordenar == C_PASOS){ordenar = 0; /*FastLED.show();*/}
 
    
    
    }
  
  
  
  
  
  }

boolean check (boolean cual, int entrada, int ds){

  boolean resu = false;
  
  if(cual){ if(digitalRead(entrada) == 1){delay(ds);if(digitalRead(entrada)==1){resu = true;}}
  }else{    if(digitalRead(entrada) == 0){delay(ds);if(digitalRead(entrada)==0){resu = true;}}}
  
  return resu;
  
  }

void reset (){
  
  paso = 0;


  digitalWrite(R_RELOJ,HIGH);
  digitalWrite(R_CHIMENEA,HIGH);
  digitalWrite(R_CAJON1,HIGH);
  digitalWrite(R_CAJON2,HIGH);
  digitalWrite(R_PFINAL,HIGH);
  digitalWrite(R_LUZ,LOW);
  digitalWrite(R_AUDIO,LOW);

  I2C_write(3 ,false , true);
  }
