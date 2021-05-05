//INCLUDES

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"


//DECLARACIONES LIB.MP3

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);



//GLOBALES

unsigned char CERRAJERO [8] = {4 , 5 , 5 , 5 , 4 , 2 , 6 , 7 };

unsigned char FLASHERA [8] = {4 , 10 , 6 , 6 , 3 , 10 , 5 , 10 };

unsigned char NUMERO [8];

boolean flag1 = true;

boolean flag2 = false;

boolean flag3 = false;

boolean flag4 = false;

boolean flag5 = false;

boolean co = true;

boolean loopeado = false;

int posicion = 0;

unsigned int numero = 0;

unsigned long prevmilis = 0;

int interval = 300 ;

int interval2 = 300;

int GH = 0;

int GF = 0;

//SETUP

void setup() {

  mySoftwareSerial.begin(9600);
  
  Serial.begin(9600);

   Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
//  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
//    Serial.println(F("Unable to begin:"));
//    Serial.println(F("1.Please recheck the connection!"));
//    Serial.println(F("2.Please insert the SD card!"));
    //while(true);
  }
//  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
  //myDFPlayer.play(1);  //Play the first mp3
  
  

  

  pinMode (3, INPUT_PULLUP);

  pinMode (2, INPUT_PULLUP);

  attachInterrupt( 0, descolgado, RISING);

  attachInterrupt( 1, contando, RISING);

}

//LOOP

void loop() {
//Serial.println(digitalRead(2));
   if(flag2 == true){

    delay(50);

   if ((unsigned long)(millis() - prevmilis) >= interval && flag1){

    if(loopeado){loopeado = false; myDFPlayer.pause();}

    prevmilis = millis();

    numero = 0;

    interval = 300;

    flag1 = false;
  
  }else{
    
    flag1 = true;

     numero++;

     prevmilis = millis();

    flag3 = true;

    interval = interval + 100;
    
    }


  
  flag2 = false;

//  Serial.println("conta");



  
  }

 if ((unsigned long)(millis() - prevmilis) >= interval2 && flag3){

//  if (numero == 10) {numero = 0;}
  
   Serial.println(numero);

  NUMERO[posicion] = numero;

  if(NUMERO[posicion] == CERRAJERO [posicion] || NUMERO[posicion] == CERRAJERO [posicion] + 1 || NUMERO[posicion] == CERRAJERO [posicion] - 1){GH++;};
  
  if(NUMERO[posicion] == FLASHERA [posicion] || NUMERO[posicion] == FLASHERA [posicion] + 1 || NUMERO[posicion] == FLASHERA [posicion] - 1){GF++;};

  posicion++;

  if(GH == 8){/*Serial.println("LLAMANDO A HANS");*/myDFPlayer.play(3);}

  if(GF == 8){/*Serial.println("LLAMANDO A FLASHERA");*/myDFPlayer.play(2);}

  if (posicion > 7){ posicion = 0;GH = 0; GF = 0; }

   flag3 = false;

  interval = 300 ;
  
  }

  if (flag4){
    
    delay(150);
    
    if(digitalRead(2)){
    
      flag4 = false;
  
      myDFPlayer.loop(1);
  
      loopeado = true;  
  
      numero = 0;
  
      posicion = 0;
  
      GH = 0; 
      
      GF = 0;
  
      co = false;
        
      }
      
      flag4 = false;
      
    }

  if (digitalRead(2) == false){

    myDFPlayer.pause();


    co = true;
//    detachInterrupt(1);

    delay(50);
    
    }

}

//FUNCIONES



void contando () {


  if(flag4 == false && co == false){
    
     flag2 = true;

     
    
  }
 
  }

void descolgado () {
  
  flag4 = true; 

  Serial.println("Uesa");
 // attachInterrupt( 1, contando, RISING);

  
  } 
