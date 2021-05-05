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

String rfidb = " 00 e5 cc 73";

//GLOBALES

int estado = 0;

boolean resua = false;

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
  digitalWrite(2,HIGH);
  pinMode(3,INPUT);
  digitalWrite(3, LOW);

  
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
                      if (rfid == rfidb){resua=true;Serial.println("OK");} else {resua=false;}
                      
                        
                        resu = true;
                        
                       
                        
                      // Terminamos la lectura de la tarjeta  actual

                      mfrc522b.PICC_HaltA();  
                             
                  }      
                  }

  if(resua && check(1,3,500)){digitalWrite(2,LOW);}
                       
         }


//NO EDITABLE
//comprueba el estado de un sensor
boolean check (boolean cual, int entrada, int ds)
{
  boolean resu = false;
  int contador = 0;  
  if(cual){ while(digitalRead(entrada) == 1 && resu == false){/*delay(ds);*/contador++;if(contador == ds){resu = true;}}
  }else{    while(digitalRead(entrada) == 0 && resu == false){/*delay(ds);*/contador++;if(contador == ds){resu = true;}}}  
  return resu; 
}
