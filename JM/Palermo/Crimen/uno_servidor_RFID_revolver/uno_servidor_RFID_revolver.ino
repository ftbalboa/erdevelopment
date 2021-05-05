/************************************
* CRIMEN-SERVIDOR-RFID REVOLVER     *
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

#include <Wire.h>

//DEFINES

#define S_REVOLVER  10    //Pin 9 para el reset del RC522

//SETUP

void setup() {

  //delay inicial
  delay(1000);

  pinMode(S_REVOLVER , INPUT);
  digitalWrite(S_REVOLVER , HIGH);
  
  //RFID
  Serial.begin(9600); //Iniciamos la comunicaciÃ³n  serial
  Serial.println("Arrancando");

  //I2C
  Wire.begin(2);                // join i2c bus with address #8
  Wire.onRequest(llama_Master); // register event
  
}

void loop() {

  int perdiendo_tiempo = 0;                                   //por las dudas del watchdog

  while(perdiendo_tiempo < 500){perdiendo_tiempo++;}
                       
         }
    

void llama_Master (){

  char c = 'N';
  
        if (digitalRead(S_REVOLVER) == 0){if(digitalRead(S_REVOLVER) == 0){c = 'Y';}} 

                  
  Wire.write(c);
  
  Serial.println(c);
  }  


