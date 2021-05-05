//INCLUDES

#include <SPI.h>
#include <MFRC522.h>

//DEFINES

#define RST_PIN  2    //Pin 9 para el reset del RC522
#define SS_PIN  3   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522

//GLOBALES

int iman = 4;
int md1 = 10; //main data
int md2 = 11;
int md3 = 12;
int md4 = 13;
int mdclk = 14;


int nd1 = 5; //nano data
int nd2 = 6;
int nd3 = 7;
int nd4 = 8;
int ndclk = 9;
int paso = 15;

int estado = 0;
int dp = 200; //delay paso 

//FLAGS





//SETUP


void setup() {
  
  //DELAY INICIAL
  delay(1000);

  //RFID
  Serial.begin(9600); //Iniciamos la comunicaciÃ³n  serial
  SPI.begin();        //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos  el MFRC522
  Serial.println("Arrancando");

  //PINMODES 

  //inputs
  pinMode(iman, INPUT);
  digitalWrite(iman , HIGH);
  pinMode(md1, INPUT);
  pinMode(md2, INPUT);
  pinMode(md3, INPUT);
  pinMode(md4, INPUT);
  pinMode(mdclk, INPUT);

  //outputs
  pinMode(nd1, OUTPUT);
  pinMode(nd2, OUTPUT);
  pinMode(nd3, OUTPUT);
  pinMode(nd4, OUTPUT);
  pinMode(ndclk, OUTPUT);
  pinMode(paso, OUTPUT);
  
}

void loop() {

  seteo();

  secuenciando();
  


}

void secuenciando(){
  
  if(estado == 0){

    if(digitalRead(iman) == 1){
      
      delay(10);

      if(digitalRead(iman) == 1){

        estado++;

        playVideo(estado,false);

        
        
        }
      
      }
    
    }

   if(estado == 1){

                  if ( mfrc522.PICC_ReadCardSerial()) 
              {
                    // Enviamos serialemente su UID
                    Serial.println("Card UID:");
                    String rfid = "";
                    for (byte i = 0; i < mfrc522.uid.size; i++) {
                      rfid += mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ";
                      rfid += String(mfrc522.uid.uidByte[i], HEX);
                      }   

                      estado++;

                      playVideo(estado,false);
                      
                    // Terminamos la lectura de la tarjeta  actual
                    mfrc522.PICC_HaltA();  
                           
                }      
          } 
    
    
    
    
    }
  

void playVideo (int numero , boolean who_call){

  if(who_call == false){digitalWrite(paso , 1);
                        if(numero == 9){delay(300);}
                        delay(100);
                        digitalWrite(paso , 0);                        
                        }
  
  switch(numero){
    
    case 0:

      digitalWrite(nd1 , 0);
      digitalWrite(nd2 , 0);
      digitalWrite(nd3 , 0);
      digitalWrite(nd4 , 0);
      digitalWrite(ndclk , 1);
      delay(dp);
      digitalWrite(ndclk , 0);
      delay(10000);
      digitalWrite(paso , 1);
      delay(dp);
      digitalWrite(paso , 0);
      break;

    case 1:

      digitalWrite(nd1 , 1);
      digitalWrite(nd2 , 0);
      digitalWrite(nd3 , 0);
      digitalWrite(nd4 , 0);
      digitalWrite(ndclk , 1);
      delay(dp);
      digitalWrite(ndclk , 0);
      delay(60000);
      digitalWrite(paso , 1);
      delay(dp);
      digitalWrite(paso , 0);
      break;    

    case 2:

      digitalWrite(nd1 , 0);
      digitalWrite(nd2 , 1);
      digitalWrite(nd3 , 0);
      digitalWrite(nd4 , 0);
      digitalWrite(ndclk , 1);
      delay(dp);
      digitalWrite(ndclk , 0);
      delay(38000);
      digitalWrite(paso , 1);
      delay(dp);
      digitalWrite(paso , 0);
      
      break;    
    
    case 3:

      digitalWrite(nd1 , 1);
      digitalWrite(nd2 , 1);
      digitalWrite(nd3 , 0);
      digitalWrite(nd4 , 0);
      digitalWrite(ndclk , 1);
      delay(dp);
      digitalWrite(ndclk , 0);
      delay(23000);
      digitalWrite(paso , 1);
      delay(dp);
      digitalWrite(paso , 0);

      break;

    case 4:

      digitalWrite(nd1 , 0);
      digitalWrite(nd2 , 0);
      digitalWrite(nd3 , 1);
      digitalWrite(nd4 , 0);
      digitalWrite(ndclk , 1);
      delay(dp);
      digitalWrite(ndclk , 0);
      delay(25000);
      digitalWrite(paso , 1);
      delay(dp);
      digitalWrite(paso , 0);
      break;    

    case 5:

      digitalWrite(nd1 , 1);
      digitalWrite(nd2 , 0);
      digitalWrite(nd3 , 1);
      digitalWrite(nd4 , 0);
      digitalWrite(ndclk , 1);
      delay(dp);
      digitalWrite(ndclk , 0);
      delay(40000);
      digitalWrite(paso , 1);
      delay(dp);
      digitalWrite(paso , 0);
      break; 

    case 6:

      digitalWrite(nd1 , 0);
      digitalWrite(nd2 , 1);
      digitalWrite(nd3 , 1);
      digitalWrite(nd4 , 0);
      digitalWrite(ndclk , 1);
      delay(dp);
      digitalWrite(ndclk , 0);
      delay(25000);
      digitalWrite(paso , 1);
      delay(dp);
      digitalWrite(paso , 0);
      
      break;

    case 7:

      digitalWrite(nd1 , 1);
      digitalWrite(nd2 , 1);
      digitalWrite(nd3 , 1);
      digitalWrite(nd4 , 0);
      digitalWrite(ndclk , 1);
      delay(dp);
      digitalWrite(ndclk , 0);
      delay(25000);
      digitalWrite(paso , 1);
      delay(dp);
      digitalWrite(paso , 0);
      break;    

    case 8:

      digitalWrite(nd1 , 0);
      digitalWrite(nd2 , 0);
      digitalWrite(nd3 , 0);
      digitalWrite(nd4 , 1);
      digitalWrite(ndclk , 1);
      delay(dp);
      digitalWrite(ndclk , 0);
      delay(1000);
      digitalWrite(paso , 1);
      delay(dp);
      digitalWrite(paso , 0);

      break; 
    
    case 9:

      digitalWrite(nd1 , 1);
      digitalWrite(nd2 , 0);
      digitalWrite(nd3 , 0);
      digitalWrite(nd4 , 1);
      digitalWrite(ndclk , 1);
      delay(dp);
      digitalWrite(ndclk , 0);
      delay(1000);
      digitalWrite(paso , 1);
      delay(dp);
      digitalWrite(paso , 0);
      
      break;     
    
    
    }
  
  }

void seteo(){
  
  if(digitalRead(mdclk)){

    delay(10);

    if(digitalRead(mdclk)){
      
      int lectura = 0;

      if(digitalRead(md1) == 1){delay(10);if(digitalRead(md1) == 1){lectura = lectura+1;}}
      if(digitalRead(md2) == 1){delay(10);if(digitalRead(md2) == 1){lectura = lectura+2;}}
      if(digitalRead(md3) == 1){delay(10);if(digitalRead(md3) == 1){lectura = lectura+4;}}
      if(digitalRead(md4) == 1){delay(10);if(digitalRead(md4) == 1){lectura = lectura+8;}}

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





