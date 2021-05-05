//INCLUDES

#include <VirtualWire.h>

//GLOBALES

int video0 = 2;
int video1 = 3;
int video2 = 4;
int video3 = 5;
int video4 = 6;
int video5 = 7;
int video6 = 8;
int video7 = 9;
int video8a = 13;
int video8b = 19;
int videort = 18 ;

int txx = 14;
int fin = 15;
int clk = 16;
int rst = 17;


int lope = 0;

int tx = 12;

int videon = 0;

boolean clkflag = true; 
boolean txflag = true;
boolean rstflag = true;
boolean antflag = true;
boolean finflag = false;
boolean repeatflag = false;

void setup() {
  Serial.begin(9600);

 //OUTPUTS
  
 pinMode(video0,OUTPUT);
 pinMode(video1,OUTPUT);
 pinMode(video2,OUTPUT);
 pinMode(video3,OUTPUT);
 pinMode(video4,OUTPUT);
 pinMode(video5,OUTPUT);
 pinMode(video6,OUTPUT);
 pinMode(video7,OUTPUT);
 pinMode(video8b,OUTPUT);
 pinMode(video8a,OUTPUT);
 pinMode(videort,OUTPUT);

 pinMode(tx,INPUT); // txb
 pinMode(fin,INPUT); // txa
 pinMode(clk,INPUT); // clk
 pinMode(rst,INPUT); // rst


 digitalWrite(video0,HIGH);
 digitalWrite(video1,HIGH);
 digitalWrite(video2,HIGH);
 digitalWrite(video3,HIGH);
 digitalWrite(video4,HIGH);
 digitalWrite(video5,HIGH);
 digitalWrite(video6,HIGH);
 digitalWrite(video7,HIGH);
 digitalWrite(video8a,HIGH);
 digitalWrite(video8b,HIGH);
 digitalWrite(videort,HIGH);
 
 vw_set_tx_pin(tx);          // Configura el pin 12 como TX (SETEA TX)
 vw_set_ptt_inverted(true);  // Requerido para DR3100
 vw_setup(4000);             // Bits por segundo

 playVideo(videon);

  Serial.println("reset");

}

void loop() {

  if ((digitalRead(rst)==1) && rstflag == 1){

      videon = 10;
      
      playVideo(videon);   

      delay(3000);

      videon = 0;

      playVideo(videon);

      rstflag = false;

      clkflag = true; 
      
      txflag = true;

      antflag = true;

      repeatflag = false;
      finflag = false;
      
    Serial.println("rst");
    
    } else {

        if(digitalRead(rst) == 0){
        
          rstflag = true;
          
        }
      
      }

  if (digitalRead(clk) && clkflag){

    clkflag = false;

    if(videon < 7){

      videon++;
  
      playVideo(videon);

      Serial.println(videon);

    }
    
    }else{

        if(digitalRead(clk) == 0){
        
          clkflag = true;
          
        }
      
      }

 /*       if (digitalRead(ant) && antflag){

    antflag = false;

    if(videon < 7){

      playVideo(0);

      delay(100);
  
      playVideo(videon);

      Serial.println(videon);

    }
    
    }else{

        if(digitalRead(ant) == 0){
        
          antflag = true;
          
        }
      
      }*/

   if(digitalRead(txx) && txflag && (digitalRead(fin) == 1)){

      txflag = false;

      playVideo(9);
      repeatflag = true;
      finflag = true;
      char msg[] = "B";   // Mensaje a enviar
      vw_send((uint8_t *)msg, strlen(msg)); //Enviando...
      vw_wait_tx(); // espera hasta que el mensaje se haya enviado
    
    } else {

      if(digitalRead(txx) == 0){
        
          txflag = true;
          
        }
      
      
      
      }

   if(digitalRead(txx) && txflag && (digitalRead(fin) == 0)){

      txflag = false;

      playVideo(8);
      repeatflag = true;
      finflag = false;
      char msg[] = "A";   // Mensaje a enviar
      vw_send((uint8_t *)msg, strlen(msg)); //Enviando...
      vw_wait_tx(); // espera hasta que el mensaje se haya enviado
    
    } else {
      
       if(digitalRead(txx) == 0){
        
          txflag = true;
          
        }
      
      }

if(repeatflag){
  
  if(finflag){
            if(lope > 50){
            char msg[] = "B";   // Mensaje a enviar
      vw_send((uint8_t *)msg, strlen(msg)); //Enviando...
      vw_wait_tx(); // espera hasta que el mensaje se haya enviado
      lope = 0;
      
            }
            lope++;
            delay(100);
            
    }else{
      
            if(lope > 50){
            char msg[] = "A";   // Mensaje a enviar
      vw_send((uint8_t *)msg, strlen(msg)); //Enviando...
      vw_wait_tx(); // espera hasta que el mensaje se haya enviado
      lope = 0;
      
            }
            lope++;
            delay(100);
      }
  
  
  
  
  
  }


}

void playVideo(int numero){

 digitalWrite(video0,HIGH);
 digitalWrite(video1,HIGH);
 digitalWrite(video2,HIGH);
 digitalWrite(video3,HIGH);
 digitalWrite(video4,HIGH);
 digitalWrite(video5,HIGH);
 digitalWrite(video6,HIGH);
 digitalWrite(video7,HIGH);
 digitalWrite(video8a,HIGH);
 digitalWrite(video8b,HIGH);
 digitalWrite(videort,HIGH);
 
Serial.println(numero);
  switch(numero){
    
    case 0: digitalWrite(video0,LOW);
    break;
    case 1: digitalWrite(video1,LOW);
    break;
    case 2: digitalWrite(video2,LOW);
    break;
    case 3: digitalWrite(video3,LOW);
    break;
    case 4: digitalWrite(video4,LOW);
    break;
    case 5: digitalWrite(video5,LOW);
    break;
    case 6: digitalWrite(video6,LOW);
    break;
    case 7: digitalWrite(video7,LOW);
    break;
    case 8: digitalWrite(video8a,LOW);
    break;
    case 9: digitalWrite(video8b,LOW);
    break;
    case 10: digitalWrite(videort,LOW);
    break;
   
    
    }

 

  }

