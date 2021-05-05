
#include <MFRC522.h>



/** Reset      9                5                 RST
   SPI SS     10               53                SDA


   SPI MOSI   11               51                MOSI
   SPI MISO   12               50                MISO
   SPI SCK    13               52                SCK


*/



#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above
#define RST_PIN2         8          // Configurable, see typical pin layout above
#define SS_PIN2          6
#define RST_PIN3         7         // Configurable, see typical pin layout above
#define SS_PIN3          5

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

MFRC522 mfrc5222(SS_PIN2, RST_PIN2);  // Create MFRC522 instance

MFRC522 mfrc5223(SS_PIN3, RST_PIN3);  // Create MFRC522 instance

int ledPin = 8;

void setup() {
  Serial.begin(9600);		// Initialize serial communications with the PC
  while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();			// Init SPI bus
  delay(500);
  mfrc522.PCD_Init();		// Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
  delay(500);
  mfrc5222.PCD_Init();   // Init MFRC522
  mfrc5222.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  delay(500);
  mfrc5223.PCD_Init();   // Init MFRC522
  mfrc5223.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  delay(500);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
  // Look for new cards
 
    if (( ! mfrc522.PICC_IsNewCardPresent()||! mfrc522.PICC_ReadCardSerial()) && (! mfrc5222.PICC_IsNewCardPresent()||! mfrc5222.PICC_ReadCardSerial()) &&  (! mfrc5223.PICC_IsNewCardPresent()|| ! mfrc5223.PICC_ReadCardSerial())) {
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

    String rfid2 = "";
     for (byte i = 0; i < mfrc5222.uid.size; i++) {
         rfid2 += mfrc5222.uid.uidByte[i] < 0x10 ? " 0" : " ";
         rfid2 += String(mfrc5222.uid.uidByte[i], HEX);
     }
     rfid2.trim();
     rfid2.toUpperCase();
    Serial.print("2      ");
     Serial.println(rfid2);

     String rfid3 = "";
     for (byte i = 0; i < mfrc5223.uid.size; i++) {
         rfid3 += mfrc5223.uid.uidByte[i] < 0x10 ? " 0" : " ";
         rfid3 += String(mfrc5223.uid.uidByte[i], HEX);
     }
     rfid3.trim();
     rfid3.toUpperCase();
    Serial.print("3      ");
     Serial.println(rfid3);
/*
C7 FB 4F 39
F6 3B A0 BB
9D 11 C3 DB
*/


    if(rfid2=="55 D3 E1 2B" && rfid=="A5 3C E0 2B" && rfid3=="EA AB DF 2B" /*rfid2=="F6 3B A0 BB" && rfid=="C7 FB 4F 39" && rfid3=="9D 11 C3 DB"*/){
        digitalWrite(ledPin, HIGH);
        
       }else{
         digitalWrite(ledPin, LOW);
        }


    }

  

}
