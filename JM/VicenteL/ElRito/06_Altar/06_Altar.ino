/* 06_Altar
 * 7/6/18
 * 
 * UNO CON ETHERNET SHIELD, SE CONECTA
 * A SERVER CON IP ESTABLECIDA
 * CONTROLA UN DFPLAYER, UNA LINEA REEDSWITCH Y UN RFID
 * 
 * 
 * 0.1 alpha
 */
/////////INCLUDES////////////
#include <Ethernet.h>
#include <SPI.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
//#include <MFRC522.h>
//////////DEFINES EDITABLES////////////
//dfplayer
#define RX_DFP_PIN  5
#define TX_DFP_PIN  6
//rfid
#define RST_PIN  2    //Pin 9 para el reset del RC522
#define SS_PIN  3   //Pin 10 para el SS (SDA) del RC522
//rele
#define RELE 4
#define IMANES 7
//////////EDITABLES//////////
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x06 };        //diferente en todos los devices, programable en router
byte ip[] = { 192, 168, 0, 106};                            //101 es el server
byte server[] = { 192, 168, 0, 101};                    
const char  PASO_ACTIVACION = '8';
const char  PASO_RESOLUCION = '8';
const char  RESPUESTA = '8';
const char  RESET = 'R';
//////////NO EDITABLES///////
unsigned long contador = 0;
boolean activo = false;
boolean resuelto = false;
boolean reset = false;
boolean reposo = false;
boolean eth_on = false;
boolean first_time_activo = true;
boolean first_time_resuelto = true;
////////CHOCLO///////////////
EthernetClient client;
//declaraciones rfid
//ma 3.3v, bma 9, na GND, bna NA, az 12, baz 11, ve 13, bve 10 
//MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522
//declaraciones dfplayer
 /******AUDIOS******
1-MOSCAS
2-RITUAL
  ******************/
SoftwareSerial mySoftwareSerial(RX_DFP_PIN, TX_DFP_PIN); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
//GLOBALES PRIVADAS
//const String MANO = " f0 22 10 a8";
//boolean flag1 = true;
////////SETUP////////////////
void setup() {
  delay(2000);                                                  //delay inicial

  //RFID
//  SPI.begin();        //Iniciamos el Bus SPI
//  mfrc522.PCD_Init(); // Iniciamos  el MFRC522
//  delay(1000);
  Serial.begin(9600);                                           //serial
  delay(1000);
  if (Ethernet.begin(mac) == 0) {                               //I
    Serial.println("Failed to configure Ethernet using DHCP");  //N
  }                                                             //T
  printIPAddress();                                                          
///////////////SETUP EDITABLE//////////////////////
  //MP3
  mySoftwareSerial.begin(9600);
  delay(500);
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
      Serial.println(F("Unable to begin:"));
      Serial.println(F("1.Please recheck the connection!"));
      Serial.println(F("2.Please insert the SD card!"));
  }
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
  pinMode(IMANES,INPUT);
  digitalWrite(IMANES,HIGH);
  pinMode(RELE, OUTPUT);
  digitalWrite(RELE,LOW);
//////////////////////////////////////////////////
}
/////////////////////LOOP/////////////////////////
void loop() {
  eth_update();/*Serial.println(digitalRead(IMANES));*/
  if_reset();
  if_reposo();
  if_activo();
  if_resuelto();
}
//////////////////////NO EDITABLE/////////////////
//imprime ip
void printIPAddress()
{
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }

  Serial.println();
}
//actualiza eth
void eth_update()
{
  if ((millis() - contador) >= 500) { // Esto lo puedes dejar como estaba, pero creo que es más ilustrativo así
    contador = millis();
    if(eth_on == false){
      if (client.connect("192.168.0.101", 23)){eth_on = true;}else{}
      }else{
        char c = client.read();
        while(c != -1){
          if(c == PASO_ACTIVACION && resuelto == false){activo = true; reposo = false;}
          if(c == RESET && reposo == false){reset = true; activo = false; resuelto = false; reposo = false;}
          if(c == PASO_RESOLUCION){if(resuelto){client.write(RESPUESTA);}}
          Serial.println(c);
          c = client.read();
          eth_on = false;c=-1;
      }
      if(eth_on == false){client.stop();contador = millis();}
    }
  }
}
//////////////////EDITAR/////////////////
//reset
void if_reset ()
{
  if(reset){
    reset = false;
    reposo = true;
    first_time_activo = true;
    first_time_resuelto = true;
    //EDITAR A COSAS A RESETEAR
    digitalWrite(RELE,LOW);
//    flag1 = true;
  }
}
//reposo
void if_reposo()
{
  if(reposo){
   /////////EDITAR COSAS A HACER EN REPOSO////
    
    }
}
//activo
void if_activo()
{
  if(activo){
  ////////EDITAR A COSAS A HACER CUANDO SE ACTIVA/////
 /*   if(flag1){
      if (mfrc522.PICC_IsNewCardPresent()){  /*Serial.println("activo");*/
        //Seleccionamos una tarjeta
     /*   if ( mfrc522.PICC_ReadCardSerial()) {
          // Enviamos serialemente su UID
          Serial.print("Card UID:");
          String rfid = "";
          for (byte i = 0; i < mfrc522.uid.size; i++) {
            rfid += mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ";
            rfid += String(mfrc522.uid.uidByte[i], HEX);
          }           
          mfrc522.PICC_HaltA();       eth_on = false;client.stop();  if (Ethernet.begin(mac) == 0) {                               //I
    Serial.println("Failed to configure Ethernet using DHCP");  //N
  }                                                             //T
  delay(8000);*/
  /*flag1 = false;*/  
 /*       }       
      }
    }
    else{*/
    
    if(digitalRead(IMANES) == 0){delay(50);if(digitalRead(IMANES) == 0){resuelto =  true; activo = false;/*myDFPlayer.pause();*/}}
       
    
    if(first_time_activo){
      first_time_activo = false;
      //EDITAR A COSAS A HACER LA PRIMERA VEZ QUE SE ACTIVA//
      myDFPlayer.loop(1);
      digitalWrite(RELE,HIGH);
    }
  }
  
}
//resuelto
void if_resuelto()
{
  if(resuelto){
  /////////EDITAR COSAS A HACER RESUELTO//////
    if(first_time_resuelto){
      first_time_resuelto = false;
      //EDITAR A COSAS A HACER LA PRIMERA VEZ
      }
    }
}

