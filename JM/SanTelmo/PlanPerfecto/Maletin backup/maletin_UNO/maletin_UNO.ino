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
2: 21 a3 e1 2b
3:F6 3B A0 BB
4:F6 3B A0 BB
TMA: dc 9a e0 2b
TMB: xx xx xx xx

*/

//RFIDS

String rfida = " 93 12 e1 2b";
String rfidb = " 21 a3 e1 2b";
String rfidc = " da 70 e1 2b";
String rfidd = " ab 2b e3 2b";
String t_maestra_b= " xx xx xx xx";
String t_maestra_a= " xx xx xx xx";
String t_reset1= " 10 ae 51 a8";
String t_reset2= " a8 32 bf 59";
String t_reset3= " 60 8a 34 a8";
String t_ac1= " 49 e0 e3 59";
String t_ac2= " d6 e3 bf 59";
String t_te1= " 13 c4 bf 59";
String t_te2= " c9 e1 c6 59";

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
boolean sigflag = false;
boolean trflag = false;

//SETUP

void setup() {

  //DELAY INICIAL
  delay(1000);

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
  digitalWrite (canonout, HIGH);
  
}

//LOOP

void loop() {
//Serial.println(digitalRead(canonin));
//Serial.println(digitalRead(canonout));
  if(digitalRead(iman) == 1){iman_flag = true;}

  if((iman_flag || digitalRead(sig) ) && video1){
    delay(10000);
Serial.println("video1");
    digitalWrite (clkout, HIGH);

    delay(1000);

    digitalWrite (clkout, LOW);

    video1 = false;

    video2 = true;

    delay(60000);

    Serial.println("fin delay");

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

                    
                      Serial.println("video2");
                          digitalWrite (clkout, HIGH);

                          delay(1000);

                          digitalWrite (clkout, LOW);

                          video2 = false;

                          video3 = true;

                          digitalWrite (canonout, HIGH);      

                          delay(38000);
                      
                      
                    // Terminamos la lectura de la tarjeta  actual
                    mfrc522.PICC_HaltA();  
                           
                }      
          } 
    
    if( digitalRead(sig)){
      
                            Serial.println("video2");
                          digitalWrite (clkout, HIGH);

                          delay(1000);

                          digitalWrite (clkout, LOW);

                          video2 = false;

                          video3 = true;

                          digitalWrite (canonout, HIGH); 
      
      }
    
    }

  if(video3){

    if(digitalRead(clkin)|| digitalRead(sig)){

    delay(200);

    if(digitalRead(clkin)|| digitalRead(sig)){
      
Serial.println("video3");
         digitalWrite (canonout, HIGH); 
      
         digitalWrite (clkout, HIGH);

         delay(3000);

         digitalWrite (clkout, LOW);

         video3 = false;

         video4 = true;

         delay(23000);
      
      }}

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

                    if (rfid==t_ac1 || rfid==t_ac2  ){
                
                      Serial.println("video3");
         digitalWrite (canonout, HIGH); 
      
         digitalWrite (clkout, HIGH);

         delay(3000);

         digitalWrite (clkout, LOW);

         video3 = false;

         video4 = true;

         delay(23000);
                      
                      }
                      
                    // Terminamos la lectura de la tarjeta  actual
                    mfrc522.PICC_HaltA();  
                           
                      
          } 

}
    
    
    }

  if(video4){

    if((digitalRead(clkin)== false)|| digitalRead(sig)){

    delay(200);

    if((digitalRead(clkin)== false)|| digitalRead(sig)){

      delay(2000);
      Serial.println("video4");
         digitalWrite (clkout, HIGH);

         delay(3000);

         digitalWrite (clkout, LOW);

         video4 = false;

         video5 = true;

         delay(25000);

         digitalWrite (canonout, LOW); 
      
      }
    }

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

                    if (rfid==t_te1 || rfid==t_te2  ){
                
                               delay(2000);
      Serial.println("video4");
         digitalWrite (clkout, HIGH);

         delay(3000);

         digitalWrite (clkout, LOW);

         video4 = false;

         video5 = true;

         delay(25000);

         digitalWrite (canonout, LOW); 
                      
                      }
                      
                    // Terminamos la lectura de la tarjeta  actual
                    mfrc522.PICC_HaltA();  
                           
                      
          } 

}
    
    
    }

    if(video5){

      if(digitalRead(canonin) == 0 || digitalRead(sig)){
        Serial.println("video5");
         digitalWrite (canonout, LOW); 
           digitalWrite (clkout, HIGH);
  
           delay(1000);
  
           digitalWrite (clkout, LOW);
  
           video5 = false;
  
           video6 = true;

           delay(40000);

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
  
                            delay(1000);
  
                            digitalWrite (clkout, LOW);
  
                            video6 = false;
  
                            video7 = true;
  
                            delay(25000);
                            
           pinMode(canonin, OUTPUT);
           digitalWrite(canonin , LOW);
           pinMode(canonout, INPUT);
           digitalWrite(canonout , HIGH);                      
                        
                        }
                        
                      // Terminamos la lectura de la tarjeta  actual
                      mfrc522.PICC_HaltA();  
                             
                  }      
            } 
    
      if(digitalRead(sig)){
        
        Serial.println("video6");
                            digitalWrite (clkout, HIGH);
  
                            delay(1000);
  
                            digitalWrite (clkout, LOW);
  
                            video6 = false;
  
                            video7 = true;
  
                            
           pinMode(canonin, OUTPUT);
           digitalWrite(canonin , LOW);
           pinMode(canonout, INPUT);
           digitalWrite(canonout , HIGH);
        
        
        }
      
    }

    if (video7){
      
            if(digitalRead(canonout) == false || digitalRead(sig)){
              
        Serial.println("video7");
        
           digitalWrite (clkout, HIGH);
  
           delay(3000);
  
           digitalWrite (clkout, LOW);
  
           video7 = false;
  
           video8 = true;

           delay(25000);
        
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
  
                            delay(1000);
  
                            digitalWrite (fin, LOW);

                            digitalWrite (tx, LOW);
  
                            video8 = false;
 
                            digitalWrite (canonout, LOW);                      
                        
                        } else {
  
                         if (rfid == rfidd || rfid==t_maestra_a ){
                           Serial.println("video8a");
                              digitalWrite (fin, LOW);

                              digitalWrite (tx, HIGH);
    
                              delay(1000);
    
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

     if (((digitalRead(rstin)==1) && rstflag == 1) || trflag){

      trflag = false;

      digitalWrite(rstout,HIGH);

      rstflag = false;
      
     pinMode(canonout, OUTPUT);

     digitalWrite (clkout, LOW);
  
     digitalWrite (tx, LOW);
     
     digitalWrite (fin, LOW);
     
     digitalWrite (canonout, LOW);

     pinMode(canonin, INPUT);
     digitalWrite(canonin , HIGH);

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

    delay(60000);

    Serial.println("finrst");
    
    } else {

        if(digitalRead(rstin) == 0){
        
          rstflag = true;

          digitalWrite(rstout,LOW);
          
        }
      
      }


if(video6 == false && video7 == false){          // Revisamos si hay nuevas tarjetas  presentes
    if ( mfrc522b.PICC_IsNewCardPresent()) 
          {  
        //Seleccionamos una tarjeta
              if ( mfrc522b.PICC_ReadCardSerial()) 
              {
                    // Enviamos serialemente su UID
                    Serial.println("Card UID:");
                    String rfid = "";
                    for (byte i = 0; i < mfrc522b.uid.size; i++) {
                      rfid += mfrc522b.uid.uidByte[i] < 0x10 ? " 0" : " ";
                      rfid += String(mfrc522b.uid.uidByte[i], HEX);
                      }           

                    Serial.println(rfid);

                    if (rfid==t_reset1 || rfid==t_reset2 || rfid==t_reset3 ){
                
                      trflag = true;
                      
                      }
                      
                    // Terminamos la lectura de la tarjeta  actual
                    mfrc522b.PICC_HaltA();  
                           
                }      
          } 

}
}




