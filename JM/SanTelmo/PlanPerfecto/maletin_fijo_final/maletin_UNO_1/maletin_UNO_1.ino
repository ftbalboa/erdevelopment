//INCLUDES

#include <SPI.h>
#include <MFRC522.h>

//DEFINES

#define RST_PIN  2    //Pin 9 para el reset del RC522
#define SS_PIN  3   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522b(SS_PIN, RST_PIN); //Creamos el objeto para el RC522

//GLOBALES//

int canonin = 16;
int md1 = 4; //main data //NO PLANEADO
int md2 = 5;
int md3 = 6; //NO PLANEADO
int md4 = 17;
int mdclk = 19;
int rx1 = 14;
int rx2 = 15;

int nd1 = 10; //nano data
int nd2 = 8;
int nd3 = 9;
int ndclk = 7;
int paso = 18;
//int canonout = 1;

int estado = 0;
int dp = 200; //delay paso 

//FLAGS

//RFIDS

String rfida = " 93 12 e1 2b";
String rfidb = " 21 a3 e1 2b";
String rfidc = " da 70 e1 2b";
String rfidd = " ab 2b e3 2b";


//SETUP


void setup() {
  
  //DELAY INICIAL
  delay(1000);

  //RFID
 // Serial.begin(9600); //Iniciamos la comunicaciÃ³n  serial
  SPI.begin();        //Iniciamos el Bus SPI
  mfrc522b.PCD_Init(); // Iniciamos  el MFRC522
 // Serial.println("Arrancando");

  //PINMODES 

  //inputs
  pinMode(canonin, INPUT);
  digitalWrite(canonin , HIGH);
  pinMode(md1, INPUT);
  pinMode(md2, INPUT);
  pinMode(md3, INPUT);
  pinMode(md4, INPUT);
  pinMode(mdclk, INPUT);
  pinMode(rx1, INPUT);
  pinMode(rx2, INPUT);

  //outputs
  pinMode(nd1, OUTPUT);
  pinMode(nd2, OUTPUT);
  pinMode(nd3, OUTPUT);
  pinMode(ndclk, OUTPUT);
  pinMode(paso, OUTPUT);
//  pinMode(canonout, OUTPUT);
//  digitalWrite(canonout , HIGH);
  
}

void loop() {

  seteo();

  secuenciando();
  


}

void secuenciando(){
  
    if(estado == 2){    
      
      if(digitalRead(rx1) == 1){
      
      delay(10);

      if(digitalRead(rx1) == 1){

        estado++;

        playVideo(estado,false);

        
        
        }
      
      }
      }
      
    if(estado == 3){
            if(digitalRead(rx2) == 1){
      
      delay(10);

      if(digitalRead(rx2) == 1){

        estado++;

        playVideo(estado,false);

        
        
        }
      
      }
      
      }
      
    if(estado == 4){            
      
      if(digitalRead(canonin) == 0){
      
      delay(100);

      if(digitalRead(canonin) == 0){

        estado++;

        playVideo(estado,false);

  //      digitalWrite (canonout, LOW); 
        
        }
      
      }}
      
    if(estado == 5){     
      
      if ( mfrc522b.PICC_IsNewCardPresent()) 
    
            {  
          //Seleccionamos una tarjeta
                if ( mfrc522b.PICC_ReadCardSerial()) 
                {
                      // Enviamos serialemente su UID
    //                  Serial.print("Card UID:");
                      String rfid = "";
                      for (byte i = 0; i < mfrc522b.uid.size; i++) {
                        rfid += mfrc522b.uid.uidByte[i] < 0x10 ? " 0" : " ";
                        rfid += String(mfrc522b.uid.uidByte[i], HEX);
                        }           
   //                   Serial.println(rfid);
                      if (rfid == rfidb ){

                                     estado++;

                                     playVideo(estado,false);
      /*                               pinMode(canonin, OUTPUT);
                                     digitalWrite(canonin , LOW);
                                     pinMode(canonout, INPUT);
                                     digitalWrite(canonout , HIGH);   */                   
                        
                        }
                        
                      // Terminamos la lectura de la tarjeta  actual
                      mfrc522b.PICC_HaltA();  
                             
                  }      
                  }
                  }
                  
    if(estado == 6){      if(digitalRead(canonin) == 0){
      
      delay(10);

      if(digitalRead(canonin) == 0){

        estado++;

        playVideo(estado,false);
 
        
        }
      
      }
      }

      
    if(estado == 7){          // Revisamos si hay nuevas tarjetas  presentes
      if ( mfrc522b.PICC_IsNewCardPresent()) 
            {  
          //Seleccionamos una tarjeta
                if ( mfrc522b.PICC_ReadCardSerial()) 
                {
                      // Enviamos serialemente su UID
        //              Serial.print("Card UID:");
                      String rfid = "";
                      for (byte i = 0; i < mfrc522b.uid.size; i++) {
                        rfid += mfrc522b.uid.uidByte[i] < 0x10 ? " 0" : " ";
                        rfid += String(mfrc522b.uid.uidByte[i], HEX);
                        }           
     //                 Serial.println(rfid);
                      if (rfid == rfidc ){
                                                 estado=8;

                                     playVideo(estado,false);
                        
                        } else {
  
                         if (rfid == rfidd ){
                                                       estado=9;

                                     playVideo(estado,false);
                          
                          }

                        }
                        
                      // Terminamos la lectura de la tarjeta  actual
                      mfrc522b.PICC_HaltA();  
                             
                  }      
            } }
    
    }
  

void playVideo (int numero , boolean who_call){

  if(who_call == false){digitalWrite(paso , 1);
                        if(numero == 9){delay(500);digitalWrite(paso , 0); }
                        delay(500);                       
                        }
  
  switch(numero){
    
    case 0:

      delay(10000);
      digitalWrite(paso , 1);
      delay(dp);
      digitalWrite(paso , 0);
      pinMode(canonin, INPUT);
      digitalWrite(canonin , HIGH);
 /*     pinMode(canonout, OUTPUT);
      digitalWrite(canonout , HIGH);*/
      break;

    case 1:


      delay(60000);
      digitalWrite(paso , 1);
      delay(dp);
      digitalWrite(paso , 0);
      break;    

    case 2:
    
      digitalWrite(nd1 , 1);
      digitalWrite(nd2 , 1);
      digitalWrite(nd3 , 1);
      digitalWrite(ndclk , 1);
      delay(dp);
      digitalWrite(ndclk , 0);
      delay(38000);
      digitalWrite(paso , 1);
      delay(dp);
      digitalWrite(paso , 0);
      
      break;    
    
    case 3:

      digitalWrite(nd1 , 0);
      digitalWrite(nd2 , 0);
      digitalWrite(nd3 , 0);
      digitalWrite(ndclk , 1);
      delay(dp);
      digitalWrite(ndclk , 0);
      delay(23000);
      digitalWrite(paso , 1);
      delay(dp);
      digitalWrite(paso , 0);
 /*     pinMode(canonin, INPUT);
      digitalWrite(canonin , HIGH);
      pinMode(canonout, OUTPUT);
      digitalWrite(canonout , HIGH);*/

      break;

    case 4:

      digitalWrite(nd1 , 1);
      digitalWrite(nd2 , 0);
      digitalWrite(nd3 , 0);
      digitalWrite(ndclk , 1);
      delay(dp);
      digitalWrite(ndclk , 0);
      delay(25000);
      digitalWrite(paso , 1);
      delay(dp);
      digitalWrite(paso , 0);
      pinMode(canonin, INPUT);
      digitalWrite(canonin , HIGH);
//      pinMode(canonout, OUTPUT);
 //     digitalWrite(canonout , LOW);  
      break;    

    case 5:

      digitalWrite(nd1 , 0);
      digitalWrite(nd2 , 1);
      digitalWrite(nd3 , 0);
      digitalWrite(ndclk , 1);
      delay(dp);
      digitalWrite(ndclk , 0);
      delay(40000);
      digitalWrite(paso , 1);
      delay(dp);
      digitalWrite(paso , 0);
/*      pinMode(canonin, OUTPUT);
      digitalWrite(canonin , LOW);
      pinMode(canonout, INPUT);
      digitalWrite(canonout , HIGH);   */
      break; 

    case 6:

      digitalWrite(nd1 , 1);
      digitalWrite(nd2 , 1);
      digitalWrite(nd3 , 0);
      digitalWrite(ndclk , 1);
      delay(dp);
      digitalWrite(ndclk , 0);
      delay(25000);
      digitalWrite(paso , 1);
      delay(dp);
      digitalWrite(paso , 0);
/*      pinMode(canonin, OUTPUT);
      digitalWrite(canonin , LOW);
      pinMode(canonout, INPUT);
      digitalWrite(canonout , HIGH);   */
      
      break;

    case 7:

      digitalWrite(nd1 , 0);
      digitalWrite(nd2 , 0);
      digitalWrite(nd3 , 1);
      digitalWrite(ndclk , 1);
      delay(dp);
      digitalWrite(ndclk , 0);
      delay(25000);
      digitalWrite(paso , 1);
      delay(dp);
      digitalWrite(paso , 0);
      break;    

    case 8:

      digitalWrite(nd1 , 1);
      digitalWrite(nd2 , 0);
      digitalWrite(nd3 , 1);
      digitalWrite(ndclk , 1);
      delay(dp);
      digitalWrite(ndclk , 0);
      delay(1000);
      digitalWrite(paso , 1);
      delay(dp);
      digitalWrite(paso , 0);

      break; 
    
    case 9:

      digitalWrite(nd1 , 0);
      digitalWrite(nd2 , 1);
      digitalWrite(nd3 , 1);
      digitalWrite(ndclk , 1);
      delay(dp);
      digitalWrite(ndclk , 0);
      delay(1000);
      digitalWrite(paso , 1);
      delay(dp);
      digitalWrite(paso , 0);
      
      break;     
    
    
    }
      digitalWrite(nd1 , 1);
      digitalWrite(nd2 , 1);
      digitalWrite(nd3 , 1);
  delay(2000);
 //Serial.println("Mande"); 
  }

void seteo(){
  
  if(digitalRead(mdclk)){

    delay(100);

    if(digitalRead(mdclk)){
      
      int lectura = 0;
      int confirmacion = 0;
      int lectura2 = 0;
while(confirmacion != 3){
      if(digitalRead(md1) == 1){delay(50);if(digitalRead(md1) == 1){lectura = lectura+1;}}
      if(digitalRead(md2) == 1){delay(50);if(digitalRead(md2) == 1){lectura = lectura+2;}}
      if(digitalRead(md3) == 1){delay(50);if(digitalRead(md3) == 1){lectura = lectura+4;}}
      if(digitalRead(md4) == 1){delay(50);if(digitalRead(md4) == 1){lectura = lectura+8;}}
      if(confirmacion == 0){lectura2 = lectura;lectura = 0;}
      if(confirmacion == 1){if (lectura == lectura2) {lectura = 0;}else{confirmacion = -1;}}
      if(confirmacion == 2){if (lectura == lectura2) {}else{confirmacion = -1;}}
      confirmacion++;

   /*   Serial.print(digitalRead(md4));
      Serial.print(digitalRead(md3));
      Serial.print(digitalRead(md2));
      Serial.println(digitalRead(md1));
Serial.println(lectura);*/
}
      if(lectura > 9){
        
        switch(lectura){
          
          case 10:

          if(lectura < 7){lectura++;      
                           estado = lectura;
                           playVideo(estado , true);}

           break;
          
          case 11:

          if(lectura > 0){if (lectura==9){lectura--;}
                           lectura--;      
                           estado = lectura;
                           playVideo(estado , true);}

           break;

          case 12:

           playVideo(estado , true);

           break;
          
          }
        
        
        
        }else{

      estado = lectura;

      playVideo(estado , true);

        }
      
      }
    
    
    
    }
  
  
  
  }






