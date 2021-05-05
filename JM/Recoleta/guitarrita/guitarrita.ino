//INCLUDES

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//DECLARACIONES LIB.MP3

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

//GLOBALES

int pulsa = 3;

//SETUP
void setup() {
delay(1000);
    mySoftwareSerial.begin(9600);
  Serial.begin(115200);
      if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.EQ(DFPLAYER_EQ_ROCK);
  
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
  //myDFPlayer.play(1);  //Play the first mp3

  pinMode(pulsa , INPUT);

  digitalWrite(pulsa , HIGH);

}

void loop() {

  if(digitalRead(pulsa) == 0){
    
    myDFPlayer.play(1);

    int a = 0;

//    while(a < 10){

//      a++;
      
 //     }

     a = 0;

     delay(60000);

    myDFPlayer.pause();

    delay(1000);
    
    }
  

}
