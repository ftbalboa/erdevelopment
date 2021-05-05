/************************************
* CRIMEN-SERVIDOR-RFID CUADRO       *
* ---------------------------       *
* ARDUINO UNO - RFID                *
* ---------------------------       *
* Comunica al main por I2C          *
* cuando el RFID indicado se coloca *
* sobre el sensor                   *
* ----------------------------------*
* V0.02 5/02/2018                   *
*************************************/

//INCLUDES

#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>

//DEFINES

#define RST_PIN  9    //Pin 9 para el reset del RC522
#define SS_PIN  10   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522b(SS_PIN, RST_PIN); //Creamos el objeto para el RC522


//RFIDS

String rfidb = " f0 22 10 a8";

//GLOBALES

int estado = 0;

boolean resu = false; int a =0;

//SETUP

void setup() {

  //delay inicial
  delay(1000);
  
  //RFID
  Serial.begin(9600); //Iniciamos la comunicaciÃ³n  serial
  SPI.begin();        //Iniciamos el Bus SPI
  mfrc522b.PCD_Init(); // Iniciamos  el MFRC522
  Serial.println("Arrancando");

  //I2C
  Wire.begin(1);                // join i2c bus with address #8
  Wire.onReceive(llama_Master2);
  Wire.onRequest(llama_Master); // register event

  
}

void loop() {

  int perdiendo_tiempo = 0;                                   //por las dudas del watchdog

  while(perdiendo_tiempo < 500){perdiendo_tiempo++;}

          if ( mfrc522b.PICC_IsNewCardPresent() || mfrc522b.PICC_ReadCardSerial()) 
    //if(true)
            {  
          //Seleccionamos una tarjeta
                if ( /*mfrc522b.PICC_ReadCardSerial()*/true) 
                {
                      // Enviamos serialemente su UID
                      Serial.print("Card UID:"); a++; Serial.print(a);
                      String rfid = "";
                      for (byte i = 0; i < mfrc522b.uid.size; i++) {
                        rfid += mfrc522b.uid.uidByte[i] < 0x10 ? " 0" : " ";
                        rfid += String(mfrc522b.uid.uidByte[i], HEX);
                        }           
                      Serial.println(rfid);
                      

                        resu = true;
                        
                       
                        
                      // Terminamos la lectura de la tarjeta  actual

                      mfrc522b.PICC_HaltA();  
                             
                  }      
                  }

  
                       
         }
    

void llama_Master (){

  char c = 'N';
  
  if(resu){c = 'Y';}
                  
  Wire.write(c);
  Serial.println(c);
  
  
  }  

void llama_Master2(){
  
    char c = 'U';
  
  // loop through all but the last
    c = Wire.read(); // receive byte as a character
             // print the character
  if(c == 'K'){resu = false;}
  
  
  
  
  
  }

