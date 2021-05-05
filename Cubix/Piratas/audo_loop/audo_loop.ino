/* AudioLoop
 * 
 * Arduino NANO, 
 * 1 DFPLAYER, 
 * 
 * loopea
 * 
 * Sputnik 11/12/20
 */

 //INCLUDES
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//DEFINES
#define TX_ADF     10
#define RX_ADF     11

#define TIEMPO_RESET 3600000


//VARIABLES
unsigned long contador_reset   = 0;



//OBJETOS

SoftwareSerial mySoftwareSerial(RX_ADF, TX_ADF);    // RX, TX
DFRobotDFPlayerMini myDFPlayer;                     //dfplayer
void printDetail(uint8_t type, int value);          //dfplayer

////////////////////////////////////SETUP///////////////////////////////
//NO EDITABLE
void setup() {
  mySoftwareSerial.begin(9600);
  Serial.println("INICIANDO");
  if (!myDFPlayer.begin(mySoftwareSerial)) {                     //Arranca dfplayer
    Serial.println(F("Unable to begin:"));
  }
  myDFPlayer.volume(20);
  myDFPlayer.play(1); 
 

}

///////////////////////////////////////LOOP//////////////////////////////////////////
void loop() {
  if(millis() - contador_reset > TIEMPO_RESET){
    myDFPlayer.play(1); 
    contador_reset = millis();
  }  
}

