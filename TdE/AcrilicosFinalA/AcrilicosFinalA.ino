/**
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read data from more than one PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 *
 * Example sketch/program showing how to read data from more than one PICC (that is: a RFID Tag or Card) using a
 * MFRC522 based RFID Reader on the Arduino SPI interface.
 *
 * Warning: This may not work! Multiple devices at one SPI are difficult and cause many trouble!! Engineering skill
 *          and knowledge are required!
 *
 * @license Released into the public domain.
 *
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS 1    SDA(SS)      ** custom, take a unused pin, only HIGH/LOW required **
 * SPI SS 2    SDA(SS)      ** custom, take a unused pin, only HIGH/LOW required **
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 */

#include <SPI.h>
#include <MFRC522.h>

#define DS            100 

#define RST_PIN         8           // Configurable, see typical pin layout above

#define SS_2_PIN        6          // Configurable, take a unused pin, only HIGH/LOW required, must be diffrent to SS 1
#define SS_3_PIN        5          // Configurable, take a unused pin, only HIGH/LOW required, must be diffrent to SS 1

#define NR_OF_READERS   2

byte ssPins[] = {SS_2_PIN, SS_3_PIN};
//originales
byte RESPUESTA1A[] = {105 ,159 ,222 ,134};
byte RESPUESTA1B[] = {205, 18, 76, 211};
//repuestos
byte RESPUESTA2A[] = {124, 209, 82, 211};
byte RESPUESTA2B[] = {224, 237, 35, 121};

byte keya[4];

byte keyb[4];

boolean retencion = false;


MFRC522 mfrc522[NR_OF_READERS];   // Create MFRC522 instance.

/**
 * Initialize.
 */
void setup() {
  pinMode(4,OUTPUT);
  pinMode(10,INPUT);
  digitalWrite(4, LOW);
  digitalWrite(10, HIGH);
  Serial.begin(9600); // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  SPI.begin();        // Init SPI bus

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
}

/**
 * Main loop.
 */
void loop() {


  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    // Look for new cards

    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
      Serial.print(F("Reader "));
      Serial.print(reader);
      // Show some details of the PICC (that is: the tag/card)
      Serial.print(F(": Card UID:"));
      dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size, reader);
      Serial.println();
 //     Serial.print(F("PICC type: "));
 //     MFRC522::PICC_Type piccType = mfrc522[reader].PICC_GetType(mfrc522[reader].uid.sak);
 //     Serial.println(mfrc522[reader].PICC_GetTypeName(piccType));

      // Halt PICC
      mfrc522[reader].PICC_HaltA();
      // Stop encryption on PCD
      mfrc522[reader].PCD_StopCrypto1();
    } //if (mfrc522[reader].PICC_IsNewC
  } //for(uint8_t reader

 boolean posa = false;
 boolean posb = false;
 int compara1 = 0;
 int compara2 = 0;
 for(byte i = 0; i < 4; i++){
  if(keya[i] == RESPUESTA1A[i]){compara1++;}
  if(keya[i] == RESPUESTA1B[i]){compara2++;}
  if(compara1 == 4 || compara2 == 4){posa = true;}
  }
 compara1 = 0;
 compara2 = 0;
 for(byte i = 0; i < 4; i++){
  if(keyb[i] == RESPUESTA2A[i]){compara1++;}
  if(keyb[i] == RESPUESTA2B[i]){compara2++;}
  if(compara1 == 4 || compara2 == 4){posb = true;}
  }

 if(posa && posb && check(0,10,DS)){
    digitalWrite(4,HIGH);
    retencion = true;
    delay(5000);
 }else{
    digitalWrite(4,LOW);
    if(retencion){
      retencion = false; 
      for(byte i = 0; i < 4; i++){
        keya[i] = 0;
        keya[i] = 0;
  } }}
  
}

/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dump_byte_array(byte *buffer, byte bufferSize, int reader) {
  for (byte i = 0; i < 4; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
    if(reader == 0){
      keya[i] = buffer[i];
      }else{
      keyb[i] = buffer[i];  
        }
    
      }
    Serial.println();
    Serial.print("A: ");
    for (byte i = 0; i < 4; i++) {
      Serial.print(keya[i]);Serial.print(' ');
      }
    Serial.println();
        Serial.print("B: ");
    for (byte i = 0; i < 4; i++) {
      Serial.print(keyb[i]);Serial.print(' ');
      }
}

//NO EDITABLE
//comprueba el estado de un sensor
boolean check (boolean cual, int entrada, int ds)
{
  boolean resu = false;
  int contador = 0;  
  if(cual){ while(digitalRead(entrada) == 1 && resu == false){contador++;if(contador == ds){resu = true;}}
  }else{    while(digitalRead(entrada) == 0 && resu == false){contador++;if(contador == ds){resu = true;}}}  
  return resu; 
}
