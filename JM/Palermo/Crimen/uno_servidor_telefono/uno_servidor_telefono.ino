/************************************
* CRIMEN-SERVIDOR-TELEFONO          *
* ---------------------------       *
* ARDUINO UNO - 1 DFPLAYER          *
* 1 TECLADO MATRICIAL               *
* ---------------------------       *
* Se comunica por I2C con el main   *
* que le dice cuando activarse y    *
* reconocer el codigo               *
*                                   *
* ----------------------------------*
* V1.02 15/02/2018                  *
*************************************/

#include <Keypad.h>
#include <Wire.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//DEFINES
#define TONO 14

//DECLARACIONES LIB.MP3

/******AUDIOS******
1-TONO
2-DETECTIVE
3-PULSACION
4-NUMERO INCORRECTO
******************/

SoftwareSerial mySoftwareSerial(2, 3); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

//TECLADO
const byte Filas = 4;  //Cuatro filas
const byte Cols = 3;   //Cuatro columnas
byte Pins_Filas[] = {7,8,9,10};//Pines Arduino a las filasbyte 
byte Pins_Cols[] = {4,5,6}; // Pines Arduino a las columnas.

char Teclas [ Filas ][ Cols ] =
 {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
 };

 Keypad Teclado1 = Keypad(makeKeymap(Teclas), Pins_Filas, Pins_Cols, Filas, Cols);

char clave[] = {'4','8','5','4','2','0','8','7'};
int longitud_clave = 8;


//FLAGS
 boolean activo = false;
 boolean claveado = false;

//GLOBALES
int estado = -1; 
int posicion = 0;
int coincidencia = 0;
unsigned int timer = 0;

void setup() {
  delay(5000);
  Serial.begin(9600) ;
  //i2c
  Wire.begin(3);                // join i2c bus with address #8
  Wire.onReceive(llama_Master); // register event
  Wire.onRequest(llama_Master2);
  //mdfp
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    
  }
  Serial.println("paso audio");

  pinMode(TONO , INPUT);
  digitalWrite(TONO , HIGH);


}

void loop() {
 //Serial.println(estado);
  secuencia(); //clavear();

}

void llama_Master() {

  char c;
  
  
    c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  

  if(c == 'A'){activo = true; estado = 0;}

  if(c == 'D'){activo = false; estado = -1;}

  if(c == 'K'){estado = 3;}

}

void secuencia() {

  switch(estado){
    
    case 0:
      if(digitalRead(TONO)==0){delay(50);if(digitalRead(TONO)==0){estado++;myDFPlayer.loop(1);}}
      posicion = 0;
      coincidencia = 0;
      claveado = false;
      break;

    case 1:
      if(claveado == false){
        clavear();
      }
      if(digitalRead(TONO)==1){delay(50);if(digitalRead(TONO)==1){estado--;myDFPlayer.pause();}}
      
      break;
      
    case 2:
     // if(timer == 5000000){myDFPlayer.play(3);timer =0;}else{timer++;} CANCELADO POR FALTA DE AUDIO
      break;
    
    }
  
  
  }

void llama_Master2(){

  char c = 'N';
  
  if(estado == 3){
    if(digitalRead(TONO) == 1){c = 'Y';};
    }

  if(estado == 2){c = 'Y';}
    
  Wire.write(c);
  
  
  
  }

void clavear (){
  
         char pulsacion = Teclado1.getKey() ; // leemos pulsacion
      if (pulsacion != 0) //Si el valor es 0 es que no se ha pulsado ninguna tecla
        {          
          Serial.println(pulsacion);
          myDFPlayer.play(3);
          if(pulsacion == clave[posicion]){coincidencia++;}
          posicion++;
          if(posicion == longitud_clave){
          claveado = true;
            if(coincidencia == longitud_clave){estado++;myDFPlayer.play(2);Serial.println("clave correcta");}else{myDFPlayer.play(4);Serial.println("clave incorrecta");}
            
            }
          }
  
  
  }
