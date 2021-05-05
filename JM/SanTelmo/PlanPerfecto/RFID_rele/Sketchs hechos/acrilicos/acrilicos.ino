
#include <DFPlayer_Mini_Mp3.h>
#include <SoftwareSerial.h>



int caja1_open=2;    
int caja1_close=3;  
int caja2_open=4;    
int caja2_close=5; 
int caja3_open=6;    
int caja3_close=7; 
int caja4_open=8;    
int caja4_close=9; 
int caja5_open=10;    
int caja5_close=11; 

int sensor = 12;
int in = 0;
int lasser_go=0;
int dvr = 30;
int bornera = 31;
int resset = 32;
int lasser = 13;
  int laser_flag;

void setup() {
   Serial.begin(9600); 
   SoftwareSerial mySerial(0, 1); // RX, TX
    mp3_set_serial (Serial);    
    mp3_set_volume (30);

  
  pinMode(caja1_open,OUTPUT);
  pinMode(caja1_close,OUTPUT);
  pinMode(caja2_open,OUTPUT);
  pinMode(caja2_close,OUTPUT);
  pinMode(caja3_open,OUTPUT);
  pinMode(caja3_close,OUTPUT);
  pinMode(caja4_open,OUTPUT);
  pinMode(caja4_close,OUTPUT);
  pinMode(caja5_open,OUTPUT);
  pinMode(caja5_close,OUTPUT);
  
  digitalWrite(caja1_open,HIGH);
  digitalWrite(caja1_close,LOW);
  digitalWrite(caja2_open,HIGH);
  digitalWrite(caja2_close,LOW);
  digitalWrite(caja3_open,HIGH);
  digitalWrite(caja3_close,LOW);
  digitalWrite(caja4_open,HIGH);
  digitalWrite(caja4_close,LOW);
  digitalWrite(caja5_open,HIGH);
  digitalWrite(caja5_close,LOW);

   pinMode(dvr,OUTPUT);
   digitalWrite(dvr,HIGH);
   pinMode (bornera, OUTPUT);
   digitalWrite(bornera,HIGH);

   pinMode (resset, OUTPUT);
   digitalWrite(resset,HIGH);

    pinMode(lasser,OUTPUT);
   digitalWrite(lasser,LOW);
   
   // delay(500);
   //mp3_play(2);
  
}

void loop() {
 int FotoResistenza = analogRead(A1); 
  

  
      if(in==0){
           if(digitalRead( sensor) == HIGH){
            mp3_play(1);
               in=1;
               lasser_go=1;     
                     digitalWrite(lasser,HIGH);
                     digitalWrite(caja1_close,HIGH);
                     digitalWrite(caja2_close,HIGH);
                     digitalWrite(caja3_close,HIGH);
                     digitalWrite(caja4_close,HIGH);
                     digitalWrite(caja5_close,HIGH);
                     delay(2000);
                     digitalWrite(caja1_open,LOW);
                     delay(500);
                     digitalWrite(caja2_open,LOW);
                     delay(500);
                     digitalWrite(caja3_open,LOW);
                     delay(500);
                     digitalWrite(caja4_open,LOW);
                     delay(500);
                     digitalWrite(caja5_open,LOW);
                      
            }
        }

        
if(lasser_go==1){

   if (FotoResistenza <= 40) {
             laser_flag=0;
             //delay(100);
             mp3_stop();
     }else{
         if(laser_flag==0){
             mp3_play(2);
             laser_flag=1;
            // delay(100);
            // Serial.println(laser_flag);
          }else{
            // laser_flag=1;
            // mp3_stop();
            }
           
           
           //delay(5000);
           
     }
            
//Serial.println(laser_flag);
  
   
 
  
  
  }        
if(digitalRead(bornera)==LOW){
   mp3_stop();
  lasser_go=0;
     digitalWrite(dvr,LOW);
     digitalWrite(lasser,LOW);
     digitalWrite(caja1_open,HIGH);
     digitalWrite(caja1_close,LOW);
     digitalWrite(caja2_open,HIGH);
     digitalWrite(caja2_close,LOW);
     digitalWrite(caja3_open,HIGH);
     digitalWrite(caja3_close,LOW);
     digitalWrite(caja4_open,HIGH);
     digitalWrite(caja4_close,LOW);
     digitalWrite(caja5_open,HIGH);
     digitalWrite(caja5_close,LOW);
  
  }else{
     digitalWrite(dvr,HIGH);
    }
if(digitalRead(resset)==LOW){ 
   mp3_stop();
in=0;
lasser_go=0;
     digitalWrite(dvr,LOW);
     digitalWrite(lasser,LOW);       
     digitalWrite(caja1_open,HIGH);
     digitalWrite(caja1_close,LOW);
     digitalWrite(caja2_open,HIGH);
     digitalWrite(caja2_close,LOW);
     digitalWrite(caja3_open,HIGH);
     digitalWrite(caja3_close,LOW);
     digitalWrite(caja4_open,HIGH);
     digitalWrite(caja4_close,LOW);
     digitalWrite(caja5_open,HIGH);
     digitalWrite(caja5_close,LOW);
}

//Serial.println(digitalRead(resset));
}
