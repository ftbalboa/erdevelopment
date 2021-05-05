#include <OneWire.h>

#define RELE_ESCARA 23
#define RELE_RFID   22

#define INTERVALO_RESET 5000
#define DELAY_RESET     250

OneWire  ds1(2);
OneWire  ds2(3);
OneWire  ds3(4);
OneWire  ds4(5);
byte addr1[8];
byte addr2[8];
byte addr3[8];
byte addr4[8];
String hey1;
String hey2;
String hey3;
String hey4;
String keyStatus1="";
String keyStatus2="";
String keyStatus3="";
String keyStatus4="";
int a1 = 0;
int a2 = 0;
int a3 = 0;
int a4 = 0;
const String ESCARA1 = "6a0125da6";
const String ESCARA2 = "6a0123c6";
const String ESCARA3 = "6a0123d93";
const String ESCARA4 = "6a0123ce1";
unsigned long contador = 0;
boolean juega = true;
boolean flag = false;
boolean flag2 = false;
boolean flag3 = false;
boolean flag4 = false;
boolean flag5 = false;


void setup(void) {
  Serial.begin(9600);
  delay(500);
  Serial.println("INICIE");
  pinMode(RELE_RFID , OUTPUT);
  digitalWrite(RELE_RFID , HIGH);
  pinMode(RELE_ESCARA , OUTPUT);
  digitalWrite(RELE_ESCARA , LOW);
}

void loop(void) {
 if(juega){
  //
  delay(100);
  getKeyCode1();
  if(keyStatus1=="ok"){
      byte i;
      Serial.print("1");
      Serial.print(" : ");
      hey1="";
      for( i = 5; i >0; i--) {
           Serial.print(addr1[i], HEX);
           hey1 += String(addr1[i], HEX);     
      }
      Serial.print(" : ");
      Serial.print(hey1);      
      keyStatus1 = "";
      a1++;
      Serial.println();flag2 = true;
flag5 = true;
  }
  else if (keyStatus1!="") { Serial.println(keyStatus1);}
  //2
  getKeyCode2();
    if(keyStatus2=="ok"){
      byte i;
      Serial.print("2");
      Serial.print(" : ");
      hey2="";
      for( i = 5; i >0; i--) {
           Serial.print(addr2[i], HEX);
           hey2 += String(addr2[i], HEX);            
      }
      Serial.print(" : ");
      Serial.print(hey2);
      keyStatus2 = "";
      a2++;
      Serial.println();flag3 = true;
flag5 = true;
  }
  else if (keyStatus2!="") { Serial.println(keyStatus2);}
  //3
    getKeyCode3();
    if(keyStatus3=="ok"){
      byte i;
      Serial.print("3");
      Serial.print(" : ");
      hey3="";
      for( i = 5; i >0; i--) {
           Serial.print(addr3[i], HEX);
           hey3 += String(addr3[i], HEX);        
      }
      Serial.print(" : ");
      Serial.print(hey3);
      keyStatus3 = "";
      a3++;
      Serial.println();flag4 = true;
flag5 = true;
  }
  else if (keyStatus3!="") { Serial.println(keyStatus3);}
  //4
    getKeyCode4();
    if(keyStatus4=="ok"){
      byte i;
      Serial.print("4");
      Serial.print(" : ");
      hey4="";
      for( i = 5; i >0; i--) {
           Serial.print(addr4[i], HEX);
           hey4 += String(addr4[i], HEX);       
      }
      Serial.print(" : ");
      Serial.print(hey4);   Serial.print(keyStatus4);    
      keyStatus4 = "";
      a4++;
      Serial.println();flag = true;
flag5 = true;
  }
  if(hey1 == ESCARA1 && hey2 == ESCARA2 && hey3 == ESCARA3 && hey4 == ESCARA4){Serial.println("OKA");digitalWrite(RELE_ESCARA, HIGH);}
  else{if(((millis() - contador) > INTERVALO_RESET) && flag /*|| flag5*/ ){hey1="";hey2="";hey3="";hey4="";digitalWrite(RELE_RFID , LOW); delay(DELAY_RESET);digitalWrite(RELE_RFID , HIGH);contador = millis();flag5=false;}digitalWrite(RELE_ESCARA, LOW);}
 }
} 
//1
void getKeyCode1(){
  byte present = 0;
  byte data[12];
  keyStatus1="";
  
  if ( !ds1.search(addr1)) {
      ds1.reset_search();//ds1.reset();
      return;
  }

  if ( OneWire::crc8( addr1, 7) != addr1[7]) {
      keyStatus1="CRC invalid";
      return;
  }
  
  if ( addr1[0] != 0x01) {
      keyStatus1="not DS1990A";
      return;
  }
  keyStatus1="ok";
 // ds1.reset();
}
//2
void getKeyCode2(){
  byte present = 0;
  byte data[12];
  keyStatus2="";
  
  if ( !ds2.search(addr2)) {
      ds2.reset_search();ds2.reset();
      return;
  }

  if ( OneWire::crc8( addr2, 7) != addr2[7]) {
      keyStatus2="CRC invalid";
      return;
  }
  
  if ( addr2[0] != 0x01) {
      keyStatus2="not DS1990A";
      return;
  }
  keyStatus2="ok";
  ds2.reset();
}
//3
void getKeyCode3(){
  byte present = 0;
  byte data[12];
  keyStatus2="";
  
  if ( !ds3.search(addr3)) {
      ds3.reset_search();ds3.reset();
      return;
  }

  if ( OneWire::crc8( addr3, 7) != addr3[7]) {
      keyStatus3="CRC invalid";
      return;
  }
  
  if ( addr3[0] != 0x01) {
      keyStatus3="not DS1990A";
      return;
  }
  keyStatus3="ok";
  ds3.reset();
}
//4
void getKeyCode4(){
  byte present = 0;
  byte data[12];
  keyStatus4="";
  
  if ( !ds4.search(addr4)) {
      ds4.reset_search();ds4.reset();
      return;
  }

  if ( OneWire::crc8( addr4, 7) != addr4[7]) {
      keyStatus4="CRC invalid";
      return;
  }
  
  if ( addr4[0] != 0x01) {
      keyStatus4="not DS1990A";
      return;
  }
  keyStatus4="ok";
  ds4.reset();
}

