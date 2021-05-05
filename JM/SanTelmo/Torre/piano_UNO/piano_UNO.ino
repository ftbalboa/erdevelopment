#include <DFPlayer_Mini_Mp3.h>

#define DS 50
 
int zamok = 13;
int zamok2 = 14;
int pin1 = 2;
int pin2 = 3;
int pin3 = 4;
int pin4 = 5;
int pin5 = 6;
int pin6 = 7;


#define Password_Lenght 7

char Master[Password_Lenght] = "123456"; //caracter
char Data[Password_Lenght];
byte data_count = 0, master_count = 0;
bool Pass_is_good;

boolean kl1 = HIGH;
boolean kl2 = HIGH;
boolean kl3 = HIGH;
boolean kl4 = HIGH;
boolean kl5 = HIGH;
boolean kl6 = HIGH;

boolean lei_uno = true;


void setup() {
  Serial.begin (9600);
  mp3_set_serial (Serial);
  delay(500);
  mp3_set_volume (15);
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
  pinMode(pin4, INPUT);
  pinMode(pin5, INPUT);
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, HIGH);
  digitalWrite(pin5, HIGH);  
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(zamok, OUTPUT);
  digitalWrite(zamok, LOW);
  pinMode(zamok2, OUTPUT);
  digitalWrite(zamok2, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
}

void loop() {

  if (digitalRead(pin1) != kl1) {
    delay(DS);
    kl1 = digitalRead(pin1);
    if (kl1 == HIGH) {
      //mp3_stop ();
    } else {
      if(data_count < Password_Lenght - 1 && lei_uno){
        Data[data_count] = '1'; // store char into data array
        //Serial.print(Data);
        data_count++;
        mp3_play (1);lei_uno = false;
      }
    }
  }
  
  if (digitalRead(pin2) != kl2) {
    delay(DS);
    kl2 = digitalRead(pin2);
    if (kl2 == HIGH) {
      //mp3_stop ();
    } else {
      if(data_count < Password_Lenght - 1 && lei_uno){
        Data[data_count] = '2'; // store char into data array
       // Serial.print(Data);
        data_count++;
        mp3_play (2);lei_uno = false;
      }
    }
  }
  
  if (digitalRead(pin3) != kl3) {
    delay(DS);
    kl3 = digitalRead(pin3);
    if (kl3 == HIGH) {
      //mp3_stop ();
    } else {
      if(data_count < Password_Lenght - 1 && lei_uno){
        Data[data_count] = '3'; // store char into data array
        //Serial.print(Data);
        data_count++;
        mp3_play (3);lei_uno = false;
      }
    }
  }
  
  if (digitalRead(pin4) != kl4) {
    delay(DS);
    kl4 = digitalRead(pin4);
    if (kl4 == HIGH) {
      //mp3_stop ();
    } else {
      if(data_count < Password_Lenght - 1 && lei_uno){
        Data[data_count] = '4'; // store char into data array
       // Serial.print(Data);
        data_count++;
        mp3_play (4);lei_uno = false;
      }
    }
  }
  
  if (digitalRead(pin5) != kl5) {
    delay(DS);
    kl5 = digitalRead(pin5);
    if (kl5 == HIGH) {
    //  mp3_stop ();
    } else {
      if(data_count < Password_Lenght - 1 && lei_uno){
        Data[data_count] = '5'; // store char into data array
        //Serial.print(Data);
        data_count++;
        mp3_play (5);lei_uno = false;
      }
    }
  }
  
  if (digitalRead(pin6) != kl6) {
    delay(DS);
    kl6 = digitalRead(pin6);
    if (kl6 == HIGH) {
  //    mp3_stop ();
    } else {
      if(data_count < Password_Lenght - 1 && lei_uno){
        Data[data_count] = '6'; // store char into data array
        //Serial.print(Data);
        data_count++;
        mp3_play (6);lei_uno = false;
      }
    }
  }

  if (data_count == 1 && Data[0] != '1') {
    clearData();
  }
  if (data_count == 2 && Data[1] != '2') {
    clearData();
  }
  if (data_count == 3 && Data[2] != '3') {
    clearData();
  }
  if (data_count == 4 && Data[3] != '4') {
    clearData();
  }
  if (data_count == 5 && Data[4] != '5') {
    clearData();
  }

  if (data_count == 1 && Data[0] == '1') {
    digitalWrite(8, HIGH);
  }
  if (data_count == 2 && Data[1] == '2') {
    digitalWrite(9, HIGH);
  }
  if (data_count == 3 && Data[2] == '3') {
    digitalWrite(10, HIGH);
  }
  if (data_count == 4 && Data[3] == '4') {
    digitalWrite(11, HIGH);
  }
  if (data_count == 5 && Data[4] == '5') {
    digitalWrite(12, HIGH);
  }



  if (data_count == Password_Lenght - 1) // if the array index is equal to the number of expected chars, compare data to master
  {

    if (!strcmp(Data, Master)) { // equal to (strcmp(Data, Master) == 0)

      digitalWrite(zamok, HIGH);
      digitalWrite(zamok2, HIGH);
      delay(10000);
      clearData();
      // mp3_stop();
      digitalWrite(zamok, LOW);
      digitalWrite(zamok2, LOW);
    } else {
      delay(3500);
      mp3_play (7);
      delay(21000);
    }
    delay(1000);// added 1 second delay to make sure the password is completely shown on screen before it gets cleared.

    clearData();

  }
  if(lei_uno == false){
    lei_uno = true;
//delay(1000);
//mp3_stop ();
}

}

void clearData()
{
  while (data_count != 0)
  {
    Data[data_count--] = 0;
  }
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);

  return;
}




