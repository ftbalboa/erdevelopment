#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>

//DEFINES
#define buzzer  6
#define RST_PIN  9    //Pin para el reset del RC522 + (11/12/13)
#define SS_PIN  10   //Pin para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522

void setup() {
  Serial.begin(9600);
  SPI.begin();        //Iniciamos el Bus SPI
  pinMode(8 , OUTPUT);
  pinMode(buzzer , OUTPUT);
  digitalWrite(8 , LOW);
}

void loop() {
  
        mfrc522.PCD_Init(); // Iniciamos  el MFRC522
      delay(100);
              // Revisamos si hay nuevas tarjetas  presentes
    if ( mfrc522.PICC_IsNewCardPresent()) 
          {  
    
                   Serial.println("Card UID:");
                          
        //Seleccionamos una tarjeta
              if ( mfrc522.PICC_ReadCardSerial()) 
              {
                    // Enviamos serialemente su UID
                      digitalWrite(8 , HIGH);
                   //   digitalWrite(6 , HIGH);
           tone(buzzer,500);
           delay(300);
           noTone(buzzer);
           tone(buzzer,600);
           delay(300);
           noTone(buzzer);
           tone(buzzer,800);
           delay(300);
           noTone(buzzer);

           
    
                    String rfid = "";
                    for (byte i = 0; i < mfrc522.uid.size; i++) {
                      rfid += mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ";
                      rfid += String(mfrc522.uid.uidByte[i], HEX);
                      }           

                    
                    Serial.println(rfid);
                      
                      
                    // Terminamos la lectura de la tarjeta  actual
                    mfrc522.PICC_HaltA();  
                           
                }delay(2000);      
          }
          delay(100);
            digitalWrite(8 , LOW);
            //digitalWrite(6 , LOW);
//Serial.println("loop");
}
