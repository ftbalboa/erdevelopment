
#include <MFRC522.h>



/** Reset      9                5                 RST
   SPI SS     10               53                SDA


   SPI MOSI   11               51                MOSI
   SPI MISO   12               50                MISO
   SPI SCK    13               52                SCK


*/



#define RST_PIN         2          // Configurable, see typical pin layout above
#define SS_PIN          3         // Configurable, see typical pin layout above


MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance


void setup() {
  Serial.begin(9600);    // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  delay(500);
  mfrc522.PCD_Init();   // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  delay(500);

  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
  // Look for new cards
 
    if ( ! mfrc522.PICC_IsNewCardPresent()||! mfrc522.PICC_ReadCardSerial() ) {
    return;
    }else{

      String rfid = "";
     for (byte i = 0; i < mfrc522.uid.size; i++) {
         rfid += mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ";
         rfid += String(mfrc522.uid.uidByte[i], HEX);
     }
     rfid.trim();
     rfid.toUpperCase();
       Serial.print("1      ");
     Serial.println(rfid);


/*
C7 FB 4F 39
F6 3B A0 BB
9D 11 C3 DB
*/




    }

  

}
