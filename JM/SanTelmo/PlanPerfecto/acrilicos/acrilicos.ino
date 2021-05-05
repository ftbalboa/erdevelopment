
#include <DFPlayer_Mini_Mp3.h>
#include <SoftwareSerial.h>
#include <VirtualWire.h>


int caja1_open=2;    
int caja1_close=3;  
int caja2_open=4;    
int caja2_close=5; 
int caja3_open=6;    
int caja3_close=40; 
int caja4_open=7;    
int caja4_close=39; 
int caja5_open=22;    
int caja5_close=38; 
int laser_rele = 36;

int telefono = 23; 
int bonenant = 0;
int bonen = 0;
int sensor = 34;
int in = 0;
int lasser_go=0;
int dvr = 30;
int bornera = 8;
int resset = 32;
int lasser = 13;
int lasser1 = 42;
int lasser2 = 43;
int lasser3 = 44;
int laser_flag = 0;
int prevmilis = 0;
boolean txflag = false;
int lope = 51;
int lope2 = 0;
int resis = 0;
int vueltas = 0;
int resis2 = 0;
int estatus = 0;
boolean resuelto = false;

void setup() {
   delay(2000);
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
       pinMode(laser_rele,OUTPUT);
   digitalWrite(laser_rele,HIGH);
    pinMode(lasser1,OUTPUT);
   digitalWrite(lasser1,LOW);
       pinMode(lasser2,OUTPUT);
   digitalWrite(lasser2,LOW);
       pinMode(lasser3,OUTPUT);
   digitalWrite(lasser3,LOW);

      pinMode (telefono, INPUT);
   digitalWrite(telefono, LOW);
   
    vw_set_tx_pin(12);          // Configura el pin 12 como TX
    vw_set_ptt_inverted(true);  // Requerido para DR3100
    vw_setup(4000);
   
   // delay(500);
   //mp3_play(2);

   cerrate();
   Serial.println("Arranque");
}

void loop() {


   unsigned int pruido = 0;
   int limite = 50;
   for(int z = 0; z < limite ; z++){
    pruido = analogRead(A0) + pruido;
    }
    pruido = pruido / limite;
       Serial.println(pruido);
 // delay(50);
 int FotoResistenza = analogRead(A1); 



 
 if(vueltas == 50){
  
  resis2 = resis / vueltas;

  resis = 0;


  vueltas = 0;

  
  } else {
    
    vueltas ++;

    resis = resis + FotoResistenza;

    
    }
    
 int sensor2 = analogRead(A3);

  //Serial.println(sensor2);
  //delay(500);
  
      if(in==0){
           if(sensor2 > 500){
               mp3_play(1);
               in=1;
               lasser_go=1;     
               cerrate();
                      char msg[] = "P";   // Mensaje a enviar
                      vw_send((uint8_t *)msg, strlen(msg)); //Enviando...
                      vw_wait_tx(); // espera hasta que el mensaje se haya enviado
                      txflag = true;
                     // Serial.println("TRAAAAAANSMITIII");
                      delay(5000);
            }
        }

        
if(lasser_go==1){
//Serial.println(resis2);
   if (resis2 <= 720 ) {
             
       if(laser_flag==0){      //delay(100);
       }
       
     }else{
         if(laser_flag==0){

         // mp3_single_loop (true);          
         mp3_play(2);
             laser_flag=1;
             //delay(1000);
            // delay(100);
            // Serial.println(laser_flag);
          }else{
            // laser_flag=1;
            //mp3_stop();
            }
           
           
           //delay(5000);
           
     }
            
//Serial.println(laser_flag);
  
   
 
  
  
  }        
/* if(digitalRead(telefono) == 1 && vueltas == 0){
  delay(100);
  if(digitalRead(telefono) == 1){*/
   
if(digitalRead(bornera) == 0 && resuelto == false){
  delay(50);
 if(digitalRead(bornera) == 0){
  if(in == 1){mp3_play(3);     digitalWrite(caja5_open,HIGH);      /*digitalWrite(caja1_open,HIGH);*/ in++;
     /* digitalWrite(caja1_close,LOW);
      digitalWrite(caja2_open,HIGH);
      digitalWrite(caja2_close,LOW);
      digitalWrite(caja3_open,HIGH);
      digitalWrite(caja3_close,LOW);
      digitalWrite(caja4_open,HIGH);
      digitalWrite(caja4_close,LOW);
      digitalWrite(caja5_open,HIGH);
      digitalWrite(caja5_close,LOW);*/
      delay(2000);resuelto=true;
      /*cerrate();*/}
 
  lasser_go=0;
     digitalWrite(dvr,LOW);
     digitalWrite(lasser,LOW);
     digitalWrite(lasser2,LOW);
     digitalWrite(lasser3,LOW);
     digitalWrite(lasser1,LOW); 
     digitalWrite(laser_rele,HIGH);
     //digitalWrite(caja1_open,HIGH);
     //digitalWrite(caja1_close,LOW);
   //  digitalWrite(caja2_open,HIGH);
     //digitalWrite(caja2_close,LOW);
   //  digitalWrite(caja3_open,HIGH);
     //digitalWrite(caja3_close,LOW);
   //  digitalWrite(caja4_open,HIGH);
     //digitalWrite(caja4_close,LOW);
     //digitalWrite(caja5_close,LOW);
 }}else{
    }
//}}
int a = 0;
while(digitalRead(resset)== 0 && a != 10){a++;
  delay(10);}
  if(a==10){
 if(digitalRead(resset)== 0){ 
  delay(1000);
  if (digitalRead(resset)== 0){
mp3_stop();
in=0;
lasser_go=0;
     digitalWrite(dvr,HIGH);
     cerrate();
     txflag = false;
     resuelto = false;
  }else{     
  
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
      delay(2000);
      /*cerrate();*/}
}
}

if(txflag && lope > 100){
      lope = 0;
    if(pruido > 800){
     char msg[] = "T";   // Mensaje a enviar
     vw_send((uint8_t *)msg, strlen(msg)); //Enviando...
     vw_wait_tx(); // espera hasta que el mensaje se haya enviado
     /*Serial.println("TRAAAAAANSMITIII P");*/}else{
      delay(15);

      char msg[] = "P";   // Mensaje a enviar
     vw_send((uint8_t *)msg, strlen(msg)); //Enviando...
     vw_wait_tx(); // espera hasta que el mensaje se haya enviado
     /*Serial.println("TRAAAAAANSMITIII T");*/     
      
      }
     
 
  }
  if(txflag){delay(10);
lope++;}
//Serial.println(digitalRead(resset));

  if(laser_flag){
    
    lope2++;
    
    }

    if(lope2 > 5000){
      lope2 = 0;
      laser_flag = false;
      }

}

void cerrate(){
  
                     digitalWrite(lasser,HIGH);
                     digitalWrite(laser_rele,LOW);
                     digitalWrite(lasser2,HIGH);
                     digitalWrite(lasser3,HIGH);
                     digitalWrite(lasser1,HIGH);
                     digitalWrite(caja1_close,HIGH);
                     digitalWrite(caja2_close,HIGH);
                     digitalWrite(caja3_close,HIGH);
                     digitalWrite(caja4_close,HIGH);
                     digitalWrite(caja5_close,HIGH);
                     delay(0);
                     digitalWrite(caja1_open,LOW);
                     delay(500);
                     digitalWrite(caja2_open,LOW);
                     delay(500);
                     digitalWrite(caja3_open,LOW);
                     delay(500);
                     digitalWrite(caja4_open,LOW);
                     delay(500);
                     digitalWrite(caja5_open,LOW);
                     delay(3000);
  }

boolean check (boolean cual, int entrada, int ds)
{
  boolean resu = false;
  int contador = 0;  
  if(cual){ while(digitalRead(entrada) == 1 && resu == false){contador++;if(contador == ds){resu = true;}}
  }else{    while(digitalRead(entrada) == 0 && resu == false){contador++;if(contador == ds){resu = true;}}}  
  return resu; 
}
