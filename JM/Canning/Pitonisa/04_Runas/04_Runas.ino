/** RUNAS_04
 * 
 * MEGA,RFID SERIAL Y RELE
 * 
 */
 /*
  * 
TAG 0 :02600343C96B8
TAG 1 :
TAG 2 :0260034EE916D
TAG 3 :026003428DDE7

  */
//INCLUDES
#include "SoftwareSerial.h"
#include "rdm630.h"
 
//EDITABLE
#define SPRINT      false
#define NEED_REPOSO false
#define RX        2
#define TX        3
#define RELE1    23
#define RELE2    22
#define DS       10

/*const int N_INPUTS = 2;
const int INPUTS[N_INPUTS] = {MEGA1,MEGA2};
const int INPUTS_ISTATE[N_INPUTS] = {1,1};*/
const int N_OUTPUTS = 2;
const int OUTPUTS[N_OUTPUTS] = {RELE1,RELE2};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,1};

const int SENSORES = 4;

String RESPUESTA0="02600343C96B8";
String RESPUESTA1="XxXxXxXxXxXxX";
String RESPUESTA2="0260034EE916D";
String RESPUESTA3="026003428DDE7";

char tag0[14];
char tag1[14];
char tag2[14];
char tag3[14];

boolean actual[] = {false,false,false,false};

char tagNumber[14];

String tagString;
String tagString1;
String tagString2;
String tagString3;
String tagString0;


//OBJETOS
rdm630 rfid2(RX, TX);  //TX-pin of RDM630 connected to Arduino pin 6

//NO EDITABLE
boolean reposo = false;
boolean activo = false;
boolean resuelto = false;
unsigned long timer_print = 0;
////////////////////////////////////SETUP///////////////////////////////
//NO EDITABLE
void setup() {
  Serial.begin(9600);
//declara entradas
/*  for(int a = 0;a < N_INPUTS;a++){ 
    pinMode(INPUTS[a] , INPUT);
    digitalWrite(INPUTS[a] , INPUTS_ISTATE[a]);
  }*/
//declara salidas
  for(int a = 0;a < N_OUTPUTS;a++){ 
    pinMode(OUTPUTS[a] , OUTPUT);
    digitalWrite(OUTPUTS[a] , OUTPUTS_ISTATE[a]);
  }
//si necesita reposo
  if(NEED_REPOSO){reposo=true;activo=false;resuelto=false;}else{reposo=false;activo=true;resuelto=false;}
//EDITABLE
  Serial1.begin(9600); // the RDM6300 runs at 9600bps
  Serial2.begin(9600); // the RDM6300 runs at 9600bps
  Serial3.begin(9600); // the RDM6300 runs at 9600bps  

}

///////////////////////////////////////LOOP//////////////////////////////////////////
void loop() {
  if_reposo();
  if_activo();
  if_resuelto();
  showme();
}

////////////////////////////////////////FUNCIONES///////////////////////////////////
//EDITABLE
void if_reposo()
{
  if(reposo){

  }
}

void if_activo()
{
  if(activo){

    int resu = 0;

    for(int a = 0;a < SENSORES;a++){

      switch(a){

        case 0:{
        
          if(lee_rdm630(a)){if(tagString0 == RESPUESTA0){actual[a] = true;}else{actual[a] = false;}if(SPRINT){Serial.println("leo0");}}
    
          if(actual[a] == true){resu++;}

  
         break;}
  
        case 1:{
        
          if(lee_rdm630(a)){if(tagString1 == RESPUESTA1){actual[a] = true;}else{actual[a] = false;}if(SPRINT){Serial.println("leo1");}}
    
          if(actual[a] == true){resu++;}

  
         break;}

        case 2:{
        
          if(lee_rdm630(a)){if(tagString2 == RESPUESTA2){actual[a] = true;}else{actual[a] = false;}if(SPRINT){/*Serial.println("leo2");*/}}
    
          if(actual[a] == true){resu++;}

  
         break;}

        case 3:{
        
          if(lee_rdm630(a)){if(tagString3 == RESPUESTA3){actual[a] = true;}else{actual[a] = false;}if(SPRINT){/*Serial.println("leo3");*/}}
    
          if(actual[a] == true){resu++;}

  
         break;}
  
        }
        
      }

    if(resu==SENSORES-2){activo=false;resuelto=true;}else{resu = 0;}
    
    }

}

void if_resuelto()
{
  if(resuelto){
    digitalWrite(RELE1,LOW);
  }
}


boolean lee_rdm630 (int cual)
{
  boolean receivedTag = false;
  switch (cual){

    case 0:
    {
      while (Serial.available()){
        unsigned long  BytesRead = Serial.readBytesUntil(3, tag0, 15);//EOT (3) is the last character in tag
        tag0[0] = '0';
        tagString0 = tag0;
        receivedTag=true; 
    } 
    break;}

    case 1:
    {
      while (Serial1.available()){
        unsigned long  BytesRead = Serial1.readBytesUntil(3, tag1, 15);//EOT (3) is the last character in tag
        tag1[0] = '0';
        tagString1 = tag1;
        receivedTag=true; 
    } 
    break;}

    case 2:
    {
      while (Serial2.available()){
        unsigned long  BytesRead = Serial2.readBytesUntil(3, tag2, 15);//EOT (3) is the last character in tag
        tag2[0] = '0';
        tagString2 = tag2;
        receivedTag=true;
    }     
    break;}

    case 3:
    {
      while (Serial3.available()){
        unsigned long  BytesRead = Serial3.readBytesUntil(3, tag3, 15);//EOT (3) is the last character in tag
        tag3[0] = '0';
        tagString3 = tag3;
        receivedTag=true;
    }     
    break;}
    
    }
  return receivedTag;   
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
      Serial.print("TAG ");
      Serial.print('0');
      Serial.print(" :");
      tagString = tag0;
      Serial.println(tagString);
      Serial.print("TAG ");
      Serial.print('1');
      Serial.print(" :");
      tagString = tag1;
      Serial.println(tagString);
      Serial.print("TAG ");
      Serial.print('2');
      Serial.print(" :");
      tagString = tag2;
      Serial.println(tagString);
      Serial.print("TAG ");
      Serial.print('3');
      Serial.print(" :");
      tagString = tag3;
      Serial.println(tagString);
    timer_print = millis();
  }
}

//NO EDITABLE
//comprueba el estado de un sensor
boolean check (boolean cual, int entrada, int ds)
{
  boolean resu = false;
  int contador = 0;  
  if(cual){ while(digitalRead(entrada) == 1 && resu == false){delay(ds);contador++;if(contador == 5){resu = true;}}
  }else{    while(digitalRead(entrada) == 0 && resu == false){delay(ds);contador++;if(contador == 5){resu = true;}}}  
  return resu; 
}
