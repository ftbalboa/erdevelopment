//INCLUDES

#include <SPI.h>
#include <MFRC522.h>

//DEFINES

#define RST_PIN  9    //Pin 9 para el reset del RC522
#define SS_PIN  10   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522

//GLOBALES

int rele = 2;

/*RFIDS
1:e7 5e ee 2b

*/

//RFIDS

String rfida = " e7 5e ee 2b";

void setup() {
  
  //RFID
  Serial.begin(9600); //Iniciamos la comunicación  serial
  SPI.begin();        //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos  el MFRC522
  Serial.println("Lectura del UID");

  pinMode(rele , OUTPUT);

  digitalWrite(rele , HIGH);
}

void loop() {
  
   if ( mfrc522.PICC_IsNewCardPresent()) 
          {  
        //Seleccionamos una tarjeta
              if ( mfrc522.PICC_ReadCardSerial()) 
              {
                    // Enviamos serialemente su UID
                    Serial.println("Card UID:");
                    String rfid = "";
                    for (byte i = 0; i < mfrc522.uid.size; i++) {
                      rfid += mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ";
                      rfid += String(mfrc522.uid.uidByte[i], HEX);
                      }           
                    Serial.println(rfid);
                    Serial.println(rfida);
                    if (rfid==rfida){
                      
                    digitalWrite(rele, LOW);

                    delay (10000);

                    digitalWrite(rele, HIGH);
                                          
                      }
                      
                    // Terminamos la lectura de la tarjeta  actual
                    mfrc522.PICC_HaltA();  
                           
                }      
          } 

}
