//INCLUDES
#include <IRremote.h>
#include <SPI.h>
#include <MFRC522.h>

//DEFINES
/*#define RST_PIN  2    //Pin para el reset del RC522 + (11/12/13)
#define SS_PIN  3   //Pin para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522*/

#define RECV_PIN  5 
IRrecv irrecv(RECV_PIN);
decode_results results;

#define IMAN   1

#define RPA    6
#define RPB    7

#define UD1    8
#define UD2    9
#define UD3    10
#define UD4    14
#define UDCLK  15
#define UDP    16

#define ACR    17
#define LED    0
#define LED2   18
#define PFA    19
#define PFB    4

//GLOBALES
int dp = 200;
int estado = -1;
boolean ftimesix = true;

void setup() {

  delay(1000);
  //Serial.begin(9600);
  //IR
  irrecv.enableIRIn(); // Empezamos la recepción  por IR
  //MFRC
/*  SPI.begin();        //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos  el MFRC522*/
  //pinModes
  pinMode(IMAN , INPUT);
  digitalWrite(IMAN , HIGH);
  pinMode(UDP , INPUT);
  
  pinMode(RPA , OUTPUT);
  digitalWrite(RPA , HIGH); 
  pinMode(RPB , OUTPUT);
  digitalWrite(RPB , HIGH);
  pinMode(UD1 , OUTPUT);
  pinMode(UD2 , OUTPUT);
  pinMode(UD3 , OUTPUT);
  pinMode(UD4 , OUTPUT);
  pinMode(UDCLK , OUTPUT);
  pinMode(ACR , OUTPUT);
  digitalWrite(ACR , HIGH);
  pinMode(LED , OUTPUT);
  pinMode(LED2 , OUTPUT);
  pinMode(PFA , OUTPUT);
  pinMode(PFB , OUTPUT);
  digitalWrite(LED2 , 0);digitalWrite(LED , 0);
  //Serial.println("LISTO");
}

void loop() {
  IR();
  secuencia();
//Serial.println(digitalRead(UDP));
}



//NO IDEA
void dump(decode_results *results) {
  // Dumps out the decode_results structure.
  // Call this after IRrecv::decode()
  
  //Serial.print("(");
  //Serial.print(results->bits, DEC);
  //Serial.print(" bits)");
  
  if (results->decode_type == UNKNOWN) {
    //Serial.print("Unknown encoding: ");
  }
  else if (results->decode_type == NEC) {
    //Serial.print("Decoded NEC: ");

  }
  else if (results->decode_type == SONY) {
    //Serial.print("Decoded SONY: ");
  }
  else if (results->decode_type == RC5) {
    //Serial.print("Decoded RC5: ");
  }
  else if (results->decode_type == RC6) {
    //Serial.print("Decoded RC6: ");
  }
  else if (results->decode_type == PANASONIC) {
    //Serial.print("Decoded PANASONIC - Address: ");
    //Serial.print(results->address, HEX);
    //Serial.print(" Value: ");
  }
  else if (results->decode_type == LG) {
    //Serial.print("Decoded LG ");
  }
  else if (results->decode_type == JVC) {
    //Serial.print("Decoded JVC ");
  }
  else if (results->decode_type == AIWA_RC_T501) {
    //Serial.print("Decoded AIWA RC T501 ");
  }
  else if (results->decode_type == WHYNTER) {
    //Serial.print("Decoded Whynter ");
  }
  //Serial.print(results->value, HEX);
  //Serial.print(" (HEX) , ");
  //Serial.print(results->value, BIN);
  //Serial.println(" (BIN)");

}

void IR (){
  
    if (irrecv.decode(&results)) {
    Serial.println(results.value);
    if(results.value == 16736925){/*Serial.println("arriba");*/};
    if(results.value == 16720605){/*Serial.println("izquierda");*/if(estado>0){if(estado == 9){estado--;}estado--; playVideo(estado);}};
    if(results.value == 16761405){/*Serial.println("derecha");*/if(estado<7){estado++; playVideo(estado);}};
    if(results.value == 16754775){/*Serial.println("abajo");*/};
    if(results.value == 16712445){/*Serial.println("OK");*/ playVideo(estado);};
    if(results.value == 16738455){/*Serial.println("1");*/estado = 1; playVideo(estado);};
    if(results.value == 16750695){/*Serial.println("2");*/estado = 2; playVideo(estado);};
    if(results.value == 16756815){/*Serial.println("3");*/estado = 3; playVideo(estado);};
    if(results.value == 16734885){/*Serial.println("9");*/estado = 9; playVideo(estado);};
    if(results.value == 16724175){/*Serial.println("4");*/estado = 4; playVideo(estado);};
    if(results.value == 16718055){/*Serial.println("5");*/estado = 5; playVideo(estado);};
    if(results.value == 16743045){/*Serial.println("6");*/estado = 6; playVideo(estado);};
    if(results.value == 16716015){/*Serial.println("7");*/estado = 7; playVideo(estado);};
    if(results.value == 16726215){/*Serial.println("8");*/estado = 8; playVideo(estado);};
    if(results.value == 16730805){/*Serial.println("0");*/estado = 0; playVideo(estado);};
    if(results.value == 16728765){/*Serial.println("asterisco");*/    digitalWrite(ACR , 0);
    delay(800);
    digitalWrite(ACR , 1);};
    if(results.value == 16732845){/*Serial.println("numeral");*/      digitalWrite(ACR , 0);
      delay(2000);
      digitalWrite(ACR , 1);};
    irrecv.resume(); // empezamos una nueva recepción
      

  } 
  }

  void playVideo(int numero){
digitalWrite(LED2 , 1);
      boolean paso = true;
    
      switch(numero){

    
    case 0:
      ftimesix = true;
      digitalWrite(ACR , 0);
      delay(2000);
      digitalWrite(ACR , 1);
      digitalWrite(UD1 , 0);
      digitalWrite(UD2 , 0);
      digitalWrite(UD3 , 0);
      digitalWrite(UD4 , 0);
      digitalWrite(UDCLK , 1);
      paso = true;
      while(paso){if(digitalRead(UDP)==1){delay(100);if(digitalRead(UDP)==1){paso = false;}}}
      digitalWrite(UDCLK , 0);
      digitalWrite(LED , 1);
      break;

    case 1:
    
      digitalWrite(LED , 0);
      digitalWrite(RPA , 0);
      digitalWrite(UD1 , 1);
      digitalWrite(UD2 , 0);
      digitalWrite(UD3 , 0);
      digitalWrite(UD4 , 0);
      digitalWrite(UDCLK , 1);
      paso = true;
      while(paso){if(digitalRead(UDP)==1){delay(100);if(digitalRead(UDP)==1){paso = false;}}}
      digitalWrite(UDCLK , 0);
      digitalWrite(RPA , 1);
      break;    

    case 2:

      digitalWrite(RPB , 0);
      digitalWrite(UD1 , 0);
      digitalWrite(UD2 , 1);
      digitalWrite(UD3 , 0);
      digitalWrite(UD4 , 0);
      digitalWrite(UDCLK , 1);
      paso = true;
      while(paso){if(digitalRead(UDP)==1){delay(100);if(digitalRead(UDP)==1){paso = false;}}}
      digitalWrite(UDCLK , 0);
      digitalWrite(RPB , 1);
      break;    
    
    case 3:

      digitalWrite(UD1 , 1);
      digitalWrite(UD2 , 1);
      digitalWrite(UD3 , 0);
      digitalWrite(UD4 , 0);
      digitalWrite(UDCLK , 1);
      paso = true;
      while(paso){if(digitalRead(UDP)){delay(50);if(digitalRead(UDP)){paso = false;}}}
      digitalWrite(UDCLK , 0);

      break;

    case 4:

      digitalWrite(UD1 , 0);
      digitalWrite(UD2 , 0);
      digitalWrite(UD3 , 1);
      digitalWrite(UD4 , 0);
      digitalWrite(UDCLK , 1);
      paso = true;
      while(paso){if(digitalRead(UDP)){delay(50);if(digitalRead(UDP)){paso = false;}}}
      digitalWrite(UDCLK , 0); 
      break;    

    case 5:

      digitalWrite(UD1 , 1);
      digitalWrite(UD2 , 0);
      digitalWrite(UD3 , 1);
      digitalWrite(UD4 , 0);
      digitalWrite(UDCLK , 1);
      paso = true;
      while(paso){if(digitalRead(UDP)){delay(50);if(digitalRead(UDP)){paso = false;}}}
      digitalWrite(UDCLK , 0);
      break; 

    case 6:

      digitalWrite(UD1 , 0);
      digitalWrite(UD2 , 1);
      digitalWrite(UD3 , 1);
      digitalWrite(UD4 , 0);
      digitalWrite(UDCLK , 1);
      paso = true;
      while(paso){if(digitalRead(UDP)){delay(50);if(digitalRead(UDP)){paso = false;}}}
      digitalWrite(UDCLK , 0);
      
      break;

    case 7:

      digitalWrite(UD1 , 1);
      digitalWrite(UD2 , 1);
      digitalWrite(UD3 , 1);
      digitalWrite(UD4 , 0);
      digitalWrite(UDCLK , 1);
      paso = true;
      while(paso){if(digitalRead(UDP)){delay(50);if(digitalRead(UDP)){paso = false;}}}
      digitalWrite(UDCLK , 0);
      break;    

    case 8:

      digitalWrite(UD1 , 0);
      digitalWrite(UD2 , 0);
      digitalWrite(UD3 , 0);
      digitalWrite(UD4 , 1);
      digitalWrite(UDCLK , 1);
      paso = true;
      while(paso){if(digitalRead(UDP)){delay(50);if(digitalRead(UDP)){paso = false;}}}
      digitalWrite(UDCLK , 0);
      digitalWrite(PFA , 1);
      delay(1000);
      digitalWrite(PFA , 0);
      
      break; 
    
    case 9:
    
      digitalWrite(UD1 , 1);
      digitalWrite(UD2 , 0);
      digitalWrite(UD3 , 0);
      digitalWrite(UD4 , 1);
      digitalWrite(UDCLK , 1);
      paso = true;
      while(paso){if(digitalRead(UDP)){delay(50);if(digitalRead(UDP)){paso = false;}}}
      digitalWrite(UDCLK , 0);
      digitalWrite(PFB , 1);
      delay(1000);
      digitalWrite(PFB , 0);
      break;   

    case 10:

      digitalWrite(UD1 , 0);
      digitalWrite(UD2 , 1);
      digitalWrite(UD3 , 0);
      digitalWrite(UD4 , 1);
      digitalWrite(UDCLK , 1);
      paso = true;
      while(paso){if(digitalRead(UDP)){delay(50);if(digitalRead(UDP)){paso = false;}}}
      digitalWrite(UDCLK , 0);
      
      break;   

      case 11:

      digitalWrite(UD1 , 1);
      digitalWrite(UD2 , 1);
      digitalWrite(UD3 , 0);
      digitalWrite(UD4 , 1);
      digitalWrite(UDCLK , 1);
      paso = true;
      while(paso){if(digitalRead(UDP)){delay(50);if(digitalRead(UDP)){paso = false;}}}
      digitalWrite(UDCLK , 0);
      
      break;   

          case 12:

      digitalWrite(UD1 , 0);
      digitalWrite(UD2 , 0);
      digitalWrite(UD3 , 1);
      digitalWrite(UD4 , 1);
      digitalWrite(UDCLK , 1);
      paso = true;
      while(paso){if(digitalRead(UDP)){delay(50);if(digitalRead(UDP)){paso = false;}}}
      digitalWrite(UDCLK , 0);
      
      break;   

 

      }
   //    Serial.print(digitalRead(UD4));
   //   Serial.print(digitalRead(UD3));
   // Serial.print(digitalRead(UD2));
   //   Serial.println(digitalRead(UD1));
   //   Serial.println(estado);
delay(1000);
digitalWrite(LED2 , 0);
    
    
    }
    
void secuencia (){
  
  switch(estado){
    
    case 0:
ftimesix = true;
       if(digitalRead(IMAN)==1){if(digitalRead(IMAN)==1){estado++;playVideo(estado);}}

    break;

    case 1:
    ftimesix = true;
  //    mfrc522.PCD_Init(); // Iniciamos  el MFRC522
      delay(5000);
              // Revisamos si hay nuevas tarjetas  presentes
/*    if ( mfrc522.PICC_IsNewCardPresent()) 
          {  
    
                          
        //Seleccionamos una tarjeta
              if ( mfrc522.PICC_ReadCardSerial()) 
              {
                    // Enviamos serialemente su UID
                    //Serial.println("Card UID:");
                    String rfid = "";
                    for (byte i = 0; i < mfrc522.uid.size; i++) {
                      rfid += mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ";
                      rfid += String(mfrc522.uid.uidByte[i], HEX);
                      } */          

                    
                    estado++;playVideo(estado);
                      
                      
                   /* // Terminamos la lectura de la tarjeta  actual
                    mfrc522.PICC_HaltA();  
                           
                }      
          }*/

    break;

    case 2:
    ftimesix = true;
    detect();

    break;
    
    case 3:
    ftimesix = true;
    detect();

    break;

    case 4:
    ftimesix = true;
    detect();

    break;


    case 5:
    ftimesix = true;
    detect();

    break;


    case 6:
    
    if(ftimesix){ftimesix = false;       
    digitalWrite(ACR , 0);
    delay(800);
    digitalWrite(ACR , 1);}
    
    detect();

    break;


    case 7:
    ftimesix = true;
    detectfin();

    break;
    
    }
  
  
  }    
    
    
 void detect(){
  boolean dtt = true;
  if(digitalRead(UDP) == 1){delay(100);if (digitalRead(UDP) == 1){digitalWrite(LED2 , 1);estado++;while(dtt){if(digitalRead(UDP) == 0){delay(200);if(digitalRead(UDP) == 0){dtt = false;}}}digitalWrite(LED2 , 0);}}

  }   
    
void detectfin(){
  
  if(digitalRead(UDP) == 1){delay(100);if (digitalRead(UDP) == 1){delay(500); if(digitalRead(UDP)==0){delay(50);if(digitalRead(UDP)==0){      
      digitalWrite(PFB , 1);
      digitalWrite(LED2 , 1);
      delay(1000);
      digitalWrite(PFB , 0);estado=8;}else{
      digitalWrite(LED2 , 1);    
      digitalWrite(PFA , 1);
      delay(1000);
      digitalWrite(PFA , 0);estado=9;}}else
      digitalWrite(LED2 , 1);    
      digitalWrite(PFA , 1);
      delay(1000);
      digitalWrite(PFA , 0);estado=9;      
      }}
      ftimesix = true;
  }    
    
    
    
    
    
