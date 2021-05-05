/* GRITOS_DINO
 * 
 * MEGA, BOTONES, AUDIO, RELE
 * 
 */

//INCLUDES
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
 
//EDITABLE
#define SPRINT true
#define NEED_REPOSO false
#define RELE    25
#define PAL0    27
#define PAL1    23
#define BOT     22
#define LUZ     12
#define RS      26



#define DS    5000
const int N_INPUTS = 4;
const int INPUTS[N_INPUTS] = {BOT, PAL0, PAL1, RS};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1,1};
const int N_OUTPUTS = 2;
const int OUTPUTS[N_OUTPUTS] = {RELE, LUZ};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,0};

int lugar = 0;



//NO EDITABLE
boolean reposo = true;
boolean activo = false;
boolean resuelto = false;
unsigned long timer_print = 0;
unsigned long timer_uesa = 0;

//OBJETOS
SoftwareSerial mySoftwareSerial(A0, 3);    // RX, TX
DFRobotDFPlayerMini myDFPlayer;                     //dfplayer
void printDetail(uint8_t type, int value);          //dfplayer
LiquidCrystal_I2C lcd(0x27, 16,2);

const byte Filas = 4;  //Cuatro filas
const byte Cols = 4;   //Cuatro columnas
byte Pins_Cols[] = {8,9,10,11};//Pines Arduino a las filasbyte 
byte Pins_Filas[] = {4,5,6,7}; // Pines Arduino a las columnas.
//no utilizar los pines 1 y 0 para no interferir en Rx y Tx

char Teclas [ Filas ][ Cols ] =
 {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
 };

const char codigoSecreto[4] = {'3','A','B','2'}; // Aqui va el codigo secreto
char claveAct[4] = {'0','0','0','0'};

int posicion=0;    // necesaria para la clave
int posicion2=0;    // necesaria para la clave
int cursor=0;      // posicion inicial de la clave en el LCD
int clave=0;       // para el LCD
int luz=0;         // para el LCD
int tiempo=0;      // para el LCD
boolean correcto = false;


Keypad Teclado1 = Keypad(makeKeymap(Teclas), Pins_Filas, Pins_Cols, Filas, Cols);

////////////////////////////////////SETUP///////////////////////////////
//NO EDITABLE
void setup() {
  if(SPRINT){Serial.begin(9600);} 
//declara entradas
  for(int a = 0;a < N_INPUTS;a++){ 
    pinMode(INPUTS[a] , INPUT);
    digitalWrite(INPUTS[a] , INPUTS_ISTATE[a]);
  }
//declara salidas
  for(int a = 0;a < N_OUTPUTS;a++){ 
    pinMode(OUTPUTS[a] , OUTPUT);
    digitalWrite(OUTPUTS[a] , OUTPUTS_ISTATE[a]);
  }
//EDITABLE

  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial)) {                     //Arranca dfplayer
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    Serial.println(myDFPlayer.readState()); //read mp3 state
    Serial.println(myDFPlayer.readFileCounts()); //read all file counts in SD card
  }
  lcd.begin();       // inicializamos el LCD.
  delay(1000);
  myDFPlayer.volume(15);
  lcd.setCursor(0,0);     // situamos el cursor el la posición 2 de la linea 0.
  lcd.print("Reset"); // escribimos en LCD
  lcd.setCursor(0,1);     // situamos el cursor el la posición 2 de la linea 0.
  lcd.print("Colocar huevo"); // escribimos en LCD
  lcd.setCursor(cursor,1); // cursor en la posicion de la variable, linea 1
  Serial.println("OK");
 // while(true){};

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
    if(check(0,RS,DS)){Serial.println("flash");
      reposo = false;
      activo = true;
      lcd.setCursor(0,0);     // situamos el cursor el la posición 2 de la linea 0.
      lcd.print("Incubadora      "); // escribimos en LCD
      lcd.setCursor(0,1);     // situamos el cursor el la posición 2 de la linea 0.
      lcd.print("Segura          "); // escribimos en LCD
      delay(3000);
      while(!check(1,RS,50000)){}
      lcd.setCursor(0,0);     // situamos el cursor el la posición 2 de la linea 0.
      lcd.print("ALARMA          "); // escribimos en LCD
      lcd.setCursor(0,1);     // situamos el cursor el la posición 2 de la linea 0.
      lcd.print("Codigo:         "); // escribimos en LCD
      myDFPlayer.loop(1);
      }
  }
}

void if_activo()
{
  if(activo){

      lcd.setCursor(8,1);     // situamos el cursor el la posición 2 de la linea 0.
      
      char pulsacion = Teclado1.getKey() ; // leemos pulsacion
      if (pulsacion != 0) //Si el valor es 0 es que no se ha pulsado ninguna tecla
        { // descartamos almohadilla y asterisco
          if (pulsacion != '#' && pulsacion != '*' && clave==0)
           { 
            int digito = 1 * check(0,PAL0,DS)+ 2 * check(0,PAL1,DS);
            claveAct[digito] = pulsacion;
            lcd.setCursor(8+digito,1);
            lcd.print(" "); // imprimimos pulsacion
            lcd.setCursor(8+digito,1);
            lcd.print(claveAct[digito]); // imprimimos pulsacion
           }
      int vamo = 0;
      for (int i = 0; i < 4; i++ ){
        if(codigoSecreto[i] == claveAct[i]){
          vamo++;
        }
        if(vamo == 4){correcto = true;}else{correcto = false;}
      }

      

      
        
        
        }

   if(check(0,BOT,DS) && correcto){
    myDFPlayer.play(2);
    resuelto = true;
    activo = false;
    lcd.setCursor(0,0);     // situamos el cursor el la posición 2 de la linea 0.
    lcd.print("Alarma          "); // escribimos en LCD
    lcd.setCursor(0,1);     // situamos el cursor el la posición 2 de la linea 0.
    lcd.print("Desactivada     "); // escribimos en LCD
    }

   if( millis() - timer_uesa > 250)
    {
      digitalWrite(LUZ, !digitalRead(LUZ));
      timer_uesa = millis();
    }
   

  }
}

void if_resuelto()
{
  if(resuelto){

    digitalWrite(RELE, 0);

  }
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");timer_print = millis();
    Serial.println(reposo);
    Serial.println(activo);
    Serial.println(resuelto);

    }
  }

//NO EDITABLE
//comprueba el estado de un sensor
boolean check (boolean cual, int entrada, int ds)
{
  boolean resu = false;
  int contador = 0;  
  if(cual){ while(digitalRead(entrada) == 1 && resu == false){/*delay(ds);*/contador++;if(contador == DS){resu = true;}}
  }else{    while(digitalRead(entrada) == 0 && resu == false){/*delay(ds);*/contador++;if(contador == DS){resu = true;}}}  
  return resu; 
}
