//INCLUDES
#include <VirtualWire.h>

//GLOBALES
int rx1 = 2;
int rx2 = 3;
int nd1 = 15; 
int nd2 = 16;
int nd3 = 14;
int ndclk = 17;


int video3 = 5;
int video4 = 6;
int video5 = 7;
int video6 = 8;
int video7 = 9;
int video8a = 13;
int video8b = 19;


int rx = 12;

int estado = -1;

void setup() {
Serial.begin(9600);
 pinMode(video3,OUTPUT);
 pinMode(video4,OUTPUT);
 pinMode(video5,OUTPUT);
 pinMode(video6,OUTPUT);
 pinMode(video7,OUTPUT);
 pinMode(video8b,OUTPUT);
 pinMode(video8a,OUTPUT);

 digitalWrite(video3,HIGH);
 digitalWrite(video4,HIGH);
 digitalWrite(video5,HIGH);
 digitalWrite(video6,HIGH);
 digitalWrite(video7,HIGH);
 digitalWrite(video8a,HIGH);
 digitalWrite(video8b,HIGH);

 pinMode(nd1,INPUT); 
 pinMode(nd2,INPUT); 
 pinMode(nd3,INPUT); 
 pinMode(ndclk,INPUT);

 pinMode(rx1,OUTPUT);
 pinMode(rx2,OUTPUT);

 //RX
 vw_set_rx_pin(rx);       //Configura el pin 12 como TX
 vw_set_ptt_inverted(true); //Requerido para DR3100
 vw_setup(4000);      //  Bits por segundo
 vw_rx_start();       // Inciar el receptor

}

void loop() {
seteo();
rxx();
}

void rxx (){

    uint8_t buf[VW_MAX_MESSAGE_LEN]; //Almacenar en buffer los datos recibidos
    uint8_t buflen = VW_MAX_MESSAGE_LEN; //Determina el numero de caracteres recibidos
    if (vw_get_message(buf, &buflen)) // Si hay un mensaje recibido ejecuta...
    {
  int i; 
        Serial.print("Rx: "); //imprime Rx en el monitor serial
  
  for (i = 0; i < buflen; i++)  //rutina para impresion del mensaje recibido
  {
            char c = (buf[i]); // guarda el caracter recibido para despues imprimirlo
            Serial.print(c); //imprime el caracter recibido en el monitor serial
      Serial.print(" "); //deja un espacio en el monitor serial

if(estado == 7){
      if( c == 'P'){digitalWrite(rx1 , HIGH);}
}

if(estado == 0){
      if( c == 'T'){digitalWrite(rx2 , HIGH);}
}
  
  }
    }
}

void playVideo (int numero , boolean who_call){
  
  switch(numero){
    
    case 0:
      digitalWrite(rx1 , LOW);
      digitalWrite(video3,LOW);
      delay(23000);
      digitalWrite(video3,HIGH);
      break;

    case 1:

      digitalWrite(rx2 , LOW);
      digitalWrite(video4,LOW);
      delay(25000);
      digitalWrite(video4,HIGH);
      break;    

    case 2:

      digitalWrite(video5,LOW);
      delay(40000);
      digitalWrite(video5,HIGH);
      
      break;    
    
    case 3:

      digitalWrite(video6,LOW);
      delay(25000);
      digitalWrite(video6,HIGH);

      break;

    case 4:

      digitalWrite(video7,LOW);
      delay(25000);
      digitalWrite(video7,HIGH);
      break;    

    case 5:

      digitalWrite(video8b,LOW);
      delay(25000);
      digitalWrite(video8b,HIGH);
      break; 

    case 6:

      digitalWrite(video8a,LOW);
      delay(25000);
      digitalWrite(video8a,HIGH);  
      
      break;
    
   
    }
  
  }

void seteo(){
  
  if(digitalRead(ndclk)){

    delay(100);

    if(digitalRead(ndclk)){
      
      int lectura = 0;

      if(digitalRead(nd1) == 1){delay(50);if(digitalRead(nd1) == 1){lectura = lectura+1;}}
      if(digitalRead(nd2) == 1){delay(50);if(digitalRead(nd2) == 1){lectura = lectura+2;}}
      if(digitalRead(nd3) == 1){delay(50);if(digitalRead(nd3) == 1){lectura = lectura+4;}}

      estado = lectura;
Serial.println(lectura);
if(estado == 7){}else{
      playVideo(estado , true);
}
 
      
      }
    
    
    
    }
  
  
  
  }



