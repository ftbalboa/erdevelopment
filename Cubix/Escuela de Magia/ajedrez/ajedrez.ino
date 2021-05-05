/* Ajedrez
 * 
 * Arduino Nano, 2 RFID, 1 rele
 * 1 piston
 * 
 * 
 * Sputnik Ar
 * 21/08/25
 */

//INCLUDES
#include <rfid1.h>
#include <softspi.h>

//RESPUESTA
uchar RESPUESTAA[5] = {0x00,0xE5,0xCC,0x73};//00E5CC73
uchar RESPUESTAB[5] = {0x31,0xD8,0x4C,0x73};//31D84C73




RFID1 rfid;//create a variable type of RFID1
uchar serNumA[5]; // array to store your ID
uchar serNumB[5];

unsigned long retA = 0;
unsigned long retB = 0;

void setup(){
  delay(1000);
  pinMode(12,OUTPUT);
  digitalWrite(12,HIGH);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  Serial.begin(9600);
  Serial.println("INIT");}

void loop(){
  
  checkRFID(0);
  checkRFID(1);
  if(millis() - retA > 2000)
   {for(int a = 0; a < 4 ; a++){
     serNumA[a] = 0;
     }  retA = millis();
   }

  if(millis() - retB > 2000)
    {for(int a = 0; a < 4 ; a++){
      serNumB[a] = 0;
      }  retB = millis();
    }

  int  correctoa = 0;
  int  correctob = 0;

  for(int a = 0; a < 4 ; a++){
    if(serNumA[a] == 0){correctoa++;}  
    }
  for(int a = 0; a < 4 ; a++){
    if(serNumB[a] == 0){correctob++;}  
    }    
   // if (correctoa == 4 && correctob == 4){digitalWrite(12,HIGH);digitalWrite(13,HIGH);Serial.println("No Resuelto");} 
  }

void checkRFID(int i){
  //rfid.begin(IRQ_PIN,SCK_PIN,MOSI_PIN,MISO_PIN,NSS_PIN,RST_PIN)
  if(i==0){
    rfid.begin(6,4,5,7,3,2);
  }
  if(i==1){
    rfid.begin(6,4,5,8,3,2);
  }
  if(i==2){
    rfid.begin(2,4,5,9,3,6);
  }
  if(i==3){
    rfid.begin(2,4,5,10,3,6);
  }
  if(i==4){
    rfid.begin(2,4,5,11,3,6);
  }
  if(i==5){
    rfid.begin(2,4,5,12,3,6);
  }
  if(i==6){
    rfid.begin(2,4,5,13,3,6);
  }
  delay(100);
  rfid.init();
  uchar status;
  uchar str[MAX_LEN];
  // Search card, return card types
  status = rfid.request(PICC_REQIDL, str);
  if (status != MI_OK)
  {
    return;
  }
  // Show card type
  rfid.showCardType(str);
  //Prevent conflict, return the 4 bytes Serial number of the card
  status = rfid.anticoll(str);
  if (status == MI_OK)
  {
    if(i==0){
      memcpy(serNumA, str, 5);
      Serial.println("RFID A: ");
      rfid.showCardID(serNumA);//show the card ID
      Serial.println();
      Serial.println("RESPUESTA A: ");
      rfid.showCardID(RESPUESTAA);
      Serial.println();
      Serial.println("----------------");
      retA=millis();

    }
    if(i==1){
      memcpy(serNumB, str, 5);

      Serial.println("RFID B: ");
      rfid.showCardID(serNumB);//show the card ID
      Serial.println();
      Serial.println("RESPUESTA B: ");
      rfid.showCardID(RESPUESTAB);
      Serial.println();
      Serial.println("----------------");
      retB = millis();
    } 
  }
  delay(100);
  rfid.halt(); //command the card into sleep mode 

  int correctoa = 0;
  int correctob = 0;
  
  for(int a = 0; a < 4 ; a++){
    if(serNumA[a] == RESPUESTAA[a]){correctoa++;}  
    }
  for(int a = 0; a < 4 ; a++){
    if(serNumB[a] == RESPUESTAB[a]){correctob++;}  
    }    
    if (correctoa == 4 && correctob == 4){digitalWrite(12,LOW);digitalWrite(13,LOW);Serial.println("Resuelto");}

 
  
}
