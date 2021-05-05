//INCLUDES

#include <SPI.h>
#include <MFRC522.h>

//DEFINES

#define RST_PIN  4    //Pin 9 para el reset del RC522
#define SS_PIN  5   //Pin 10 para el SS (SDA) del RC522
#define RST_PIN2  2    //Pin 9 para el reset del RC522
#define SS_PIN2  3   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522
MFRC522 mfrc522b(SS_PIN2, RST_PIN2); //Creamos el objeto para el RC522

//GLOBALES

int iman = 6;
int rstout = 7;
int clkout = 8;
int tx = 9;
int fin = 10;
int rstin = 14;
int clkin = 15;
int canonin = 16;
int canonout = 17;
int sig = 18;


/*RFIDS
1:C7 FB 4F 39
2:F6 3B A0 BB
3:F6 3B A0 BB
4:F6 3B A0 BB
TMA:  dc 9a e0 2b
TMB:  21 a3 e1 2b

*/

//RFIDS

String rfida = " 93 12 e1 2b";
String rfidb = " d9 65 c3 db";
String rfidc = " 91 09 c3 db";
String rfidd = " 30 91 e6 ab";
String t_maestra_b= " 21 a3 e1 2b";
String t_maestra_a= " dc 9a e0 2b";

//FLAGS

boolean iman_flag = false;
boolean video1 = true;
boolean video2 = false;
boolean video3 = false;
boolean video4 = false;
boolean video5 = false;
boolean video6 = false;
boolean video7 = false;
boolean video8 = false; 
boolean video8b = false;
boolean rstflag = true;

//SETUP

void setup() {

  //RFID
  Serial.begin(9600); //Iniciamos la comunicación  serial
  SPI.begin();        //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos  el MFRC522
  mfrc522b.PCD_Init(); // Iniciamos  el MFRC522
  Serial.println("Lectura del UID");

  //PINMODES
  pinMode(sig, INPUT);
  pinMode(iman, INPUT);
  digitalWrite(iman , HIGH);
  pinMode(rstin, INPUT);
  pinMode(clkin, INPUT);
  pinMode(canonin, INPUT);
  digitalWrite(canonin , HIGH);
  pinMode(canonout, OUTPUT);
  pinMode(tx, OUTPUT);
  pinMode(fin, OUTPUT);
  pinMode(rstout, OUTPUT);
  pinMode(clkout, OUTPUT);

  digitalWrite (clkout, LOW);
  digitalWrite (rstout, LOW);
  digitalWrite (tx, LOW);
  digitalWrite (fin, LOW);
  digitalWrite (canonout, LOW);
  
}

//LOOP

void loop() {

  if(digitalRead(iman) == 1){iman_flag = true;}

  if((iman_flag || digitalRead(sig) ) && video1){
    delay(2000);
Serial.println("video1");
    digitalWrite (clkout, HIGH);

    delay(500);

    digitalWrite (clkout, LOW);

    video1 = false;

    video2 = true;

  }

  if (video2){
    
        // Revisamos si hay nuevas tarjetas  presentes
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
                    if (rfid==rfida || rfid==t_maestra_a || rfid==t_maestra_b){
                      Serial.println("video2");
                          digitalWrite (clkout, HIGH);

                          delay(500);

                          digitalWrite (clkout, LOW);

                          video2 = false;

                          video3 = true;

                          digitalWrite (canonout, HIGH);                      
                      
                      }
                      
                    // Terminamos la lectura de la tarjeta  actual
                    mfrc522.PICC_HaltA();  
                           
                }      
          } 
    
    
    }

  if(video3){

    if(digitalRead(clkin)){
Serial.println("video3");
         digitalWrite (canonout, LOW); 
      
         digitalWrite (clkout, HIGH);

         delay(3000);

         digitalWrite (clkout, LOW);

         video3 = false;

         video4 = true;
      
      }
    
    
    }

  if(video4){

    if(digitalRead(clkin)){
      Serial.println("video4");
         digitalWrite (clkout, HIGH);

         delay(3000);

         digitalWrite (clkout, LOW);

         video4 = false;

         video5 = true;
      
      }
    
    
    }

    if(video5){

      if(digitalRead(canonin) == 0){
        Serial.println("video5");
           digitalWrite (clkout, HIGH);
  
           delay(500);
  
           digitalWrite (clkout, LOW);
  
           video5 = false;
  
           video6 = true;

           digitalWrite(canonout , LOW);
        
        }
    
    
    }

    if(video6){

          // Revisamos si hay nuevas tarjetas  presentes
      if ( mfrc522b.PICC_IsNewCardPresent()) 
            {  
          //Seleccionamos una tarjeta
                if ( mfrc522b.PICC_ReadCardSerial()) 
                {
                      // Enviamos serialemente su UID
                      Serial.print("Card UID:");
                      String rfid = "";
                      for (byte i = 0; i < mfrc522b.uid.size; i++) {
                        rfid += mfrc522b.uid.uidByte[i] < 0x10 ? " 0" : " ";
                        rfid += String(mfrc522b.uid.uidByte[i], HEX);
                        }           
                      Serial.println(rfid);
                      if (rfid == rfidb || rfid==t_maestra_a || rfid==t_maestra_b){
                        Serial.println("video6");
                            digitalWrite (clkout, HIGH);
  
                            delay(500);
  
                            digitalWrite (clkout, LOW);
  
                            video6 = false;
  
                            video7 = true;
  
                            digitalWrite (canonout, HIGH);                      
                        
                        }
                        
                      // Terminamos la lectura de la tarjeta  actual
                      mfrc522.PICC_HaltA();  
                             
                  }      
            } 
    
    
    }

    if (video7){
      
            if(digitalRead(canonin) == false){
              
        Serial.println("video7");
        
           digitalWrite (clkout, HIGH);
  
           delay(3000);
  
           digitalWrite (clkout, LOW);
  
           video7 = false;
  
           video8 = true;
        
        }
      
      
      
      }




    if(video8){

          // Revisamos si hay nuevas tarjetas  presentes
      if ( mfrc522b.PICC_IsNewCardPresent()) 
            {  
          //Seleccionamos una tarjeta
                if ( mfrc522b.PICC_ReadCardSerial()) 
                {
                      // Enviamos serialemente su UID
                      Serial.print("Card UID:");
                      String rfid = "";
                      for (byte i = 0; i < mfrc522b.uid.size; i++) {
                        rfid += mfrc522b.uid.uidByte[i] < 0x10 ? " 0" : " ";
                        rfid += String(mfrc522b.uid.uidByte[i], HEX);
                        }           
                      Serial.println(rfid);
                      if (rfid == rfidc || rfid==t_maestra_b){
                         Serial.println("video8b");
                            digitalWrite (fin, HIGH);

                            digitalWrite (tx, HIGH);
  
                            delay(500);
  
                            digitalWrite (fin, LOW);

                            digitalWrite (tx, LOW);
  
                            video8 = false;
 
                            digitalWrite (canonout, LOW);                      
                        
                        } else {
  
                         if (rfid == rfidd || rfid==t_maestra_a ){
                           Serial.println("video8a");
                              digitalWrite (fin, LOW);

                              digitalWrite (tx, HIGH);
    
                              delay(500);
    
                             digitalWrite (fin, LOW);

                             digitalWrite (tx, LOW);
    
                              video8 = false;
    
                              digitalWrite (canonout, LOW);                      
                          
                          }

                        }
                        
                      // Terminamos la lectura de la tarjeta  actual
                      mfrc522.PICC_HaltA();  
                             
                  }      
            } 
    
    
    }

     if ((digitalRead(rstin)==1) && rstflag == 1){

      digitalWrite(rstout,HIGH);

      rstflag = false;
      
     pinMode(canonout, OUTPUT);

     digitalWrite (clkout, LOW);
  
     digitalWrite (tx, LOW);
     
     digitalWrite (fin, LOW);
     
     digitalWrite (canonout, LOW);

     iman_flag = false;
     video1 = true;
     video2 = false;
     video3 = false;
     video4 = false;
     video5 = false;
     video6 = false;
     video7 = false;
    video8 = false; 
    video8b = false;
      
    Serial.println("rst");

    delay(10000);
    
    } else {

        if(digitalRead(rstin) == 0){
        
          rstflag = true;

          digitalWrite(rstout,LOW);
          
        }
      
      }

  
}
