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

String rfidb = " 31 d8 4c 73";

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
  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);


  
}

void loop() {

  int perdiendo_tiempo = 0;                                   //por las dudas del watchdog

  while(perdiendo_tiempo < 500){perdiendo_tiempo++;}

          if ( mfrc522b.PICC_IsNewCardPresent() || mfrc522b.PICC_ReadCardSerial()) 
    //if(true)
            {  
          //Seleccionamos una tarjeta
                if (mfrc522b.PICC_ReadCardSerial()) 
                {
                      // Enviamos serialemente su UID
                      Serial.print("Card UID:");
                       
                      String rfid = "";
                      for (byte i = 0; i < mfrc522b.uid.size; i++) {
                        rfid += mfrc522b.uid.uidByte[i] < 0x10 ? " 0" : " ";
                        rfid += String(mfrc522b.uid.uidByte[i], HEX);
                        }           
                      Serial.println(rfid);
                      if (rfid == rfidb){digitalWrite(2,HIGH);Serial.println("OK");} else {digitalWrite(2,LOW);}
                      
                        
                        resu = true;
                        
                       
                        
                      // Terminamos la lectura de la tarjeta  actual

                      mfrc522b.PICC_HaltA();  
                             
                  }      
                  }

  
                       
         }
    
