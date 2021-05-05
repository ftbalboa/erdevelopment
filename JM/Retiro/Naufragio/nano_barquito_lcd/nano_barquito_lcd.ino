/************************************
* RETIRO-BARCO-ALONE                *
* ---------------------------       *
* ARDUINO NANO - I2C DISPLAY        *
* AND NIKITA'S DUINO                *
* ---------------------------       *
* reconoce por tres pines en binario*
* y muestra el mensaje              *
* ----------------------------------*
* V0.01 24/03/2018                  *
*************************************/


//INCLUDES

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//GLOBALES

 /* Funcion de configuracion de pines del modulo LCD/I2C 
    (Direccion,en,rw,rs,d4,d5,d6,d7,backlight,polaridad)*/
LiquidCrystal_I2C lcd(0x27, 16,2);

int cursor = 0;      // posicion inicial de la clave en el LCD
int estado = -1;

boolean sensores[3] = {false , false , false};
int ds = 50;

#define DATA0 4
#define DATA1 5
#define DATA2 6

String ccca = "0               ";
String cccb = "               0";
String ccua = "Barco fuera de  ";
String ccub = "     curso      ";
String cuca = "Ingrese         ";
String cucb = "Distancia       ";
String cuua = "Distancia       ";
String cuub = "Incorrecta      ";
String ucca = "Procesando      ";
String uccb = "Distancia       ";
String ucua = "Distancia       ";
String ucub = "Correcta        ";
String uuca = "6               ";
String uucb = "               6";
String uuua = "Error           ";
String uuub = "               7";


void setup() {
  delay(1000);
  lcd.begin();
  pinMode(DATA0 , INPUT);
  digitalWrite(DATA0 , HIGH);
  pinMode(DATA1 , INPUT);
  digitalWrite(DATA1 , HIGH);
  pinMode(DATA2 , INPUT);
  digitalWrite(DATA2 , HIGH);
}

void loop() {

  sensorea();
  int mensaje = CreateStatus();
  LcdWrite(mensaje);

/*
delay(1000);
lcd.setCursor(0,0);
lcd.print(ccua);
delay(1000);
lcd.setCursor(0,0);
lcd.print(ccub);*/
}

int CreateStatus(){
  
  int estado = 0;

  if(sensores[0]){estado++;}
  if(sensores[1]){estado = estado + 2;}
  if(sensores[2]){estado = estado + 4;}

  return estado;
  
  }

void LcdWrite(int mensaje){

  if(estado != mensaje){
    
    switch(mensaje){
      
      case 0:
           /*lcd.setCursor(0,0);
           lcd.print(ccca);
           lcd.setCursor(0,1);
           lcd.print(cccb);*/
      break;
      
      case 1:
           lcd.setCursor(0,0);
           lcd.print(ccua);
           lcd.setCursor(0,1);
           lcd.print(ccub);
      break;

      case 2:
           lcd.setCursor(0,0);
           lcd.print(cuca);
           lcd.setCursor(0,1);
           lcd.print(cucb);
      break;         
      
      case 3:
           lcd.setCursor(0,0);
           lcd.print(cuua);
           lcd.setCursor(0,1);
           lcd.print(cuub);
      break;      
      
      case 4:
           lcd.setCursor(0,0);
           lcd.print(ucca);
           lcd.setCursor(0,1);
           lcd.print(uccb);
      break;

      case 5:
           lcd.setCursor(0,0);
           lcd.print(ucua);
           lcd.setCursor(0,1);
           lcd.print(ucub);
      break;

      case 6:
           lcd.setCursor(0,0);
           lcd.print(uuca);
           lcd.setCursor(0,1);
           lcd.print(uucb);
      break;

      case 7:
           lcd.setCursor(0,0);
           lcd.print(uuua);
           lcd.setCursor(0,1);
           lcd.print(uuub);
      break;
                  
      }
    
    }

  estado = mensaje;
  
  }

  boolean check (boolean cual, int entrada, int ds){

  boolean resu = false;
  
  if(cual){ if(digitalRead(entrada) == 1){delay(ds);if(digitalRead(entrada)==1){resu = true;}}
  }else{    if(digitalRead(entrada) == 0){delay(ds);if(digitalRead(entrada)==0){resu = true;}}}
  
  return resu;
  
  }

  void sensorea(){
    
  
    int a = 0;
    sensores[a] = check(1 , DATA0 , ds);

    a++;
    sensores[a] = check(1 , DATA1 , ds);

    a++;
    sensores[a] = check(1 , DATA2 , ds);

  }
