//INCLUDES

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include <Keypad.h>

//GLOBALES

 /* Funcion de configuracion de pines del modulo LCD/I2C 
    (Direccion,en,rw,rs,d4,d5,d6,d7,backlight,polaridad)*/
 LiquidCrystal_I2C lcd(0x27, 16,2);

const byte Filas = 4;  //Cuatro filas
const byte Cols = 3;   //Cuatro columnas
byte Pins_Filas[] = {10,5,6,8};//Pines Arduino a las filasbyte 
byte Pins_Cols[] = {9,11,7}; // Pines Arduino a las columnas.
//no utilizar los pines 1 y 0 para no interferir en Rx y Tx

char Teclas [ Filas ][ Cols ] =
 {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
 };

char codigoSecreto[8] = {'2','4','0','8','1','9','9','0'}; // Aqui va el codigo secreto
char codigoSecreto2[8] = {'2','0','3','1','1','9','2','6'}; // Aqui va el codigo secreto
// Para cambiar el tamaño de la clave, solo hay que cambiar el tamaño del array

int posicion=0;    // necesaria para la clave
int posicion2=0;    // necesaria para la clave
int cursor=0;      // posicion inicial de la clave en el LCD
int clave=0;       // para el LCD
int luz=0;         // para el LCD
int tiempo=0;      // para el LCD
int buzzer= 3;     // pin altavoz
int puerta= 2;     // pin para la puerta
boolean clave2 = 0;
int puerta2 = 4;


Keypad Teclado1 = Keypad(makeKeymap(Teclas), Pins_Filas, Pins_Cols, Filas, Cols);

//SETUP

void setup()
   {
      Serial.begin(9600) ;
      lcd.begin();       // inicializamos el LCD.
    //  lcd.noBacklight();     // apagamos LCD

      pinMode (buzzer, OUTPUT);
      pinMode (puerta, OUTPUT);
      pinMode (puerta2, OUTPUT);
      digitalWrite(puerta, HIGH); // cerramos puerta
      digitalWrite(puerta2,HIGH); // cerramos puerta

      lcd.setCursor(0,0);     // situamos el cursor el la posición 2 de la linea 0.
      lcd.print("Introduzca clave"); // escribimos en LCD
      lcd.setCursor(cursor,1); // cursor en la posicion de la variable, linea 1
     
    }

//LOOP

void loop()
   {
      char pulsacion = Teclado1.getKey() ; // leemos pulsacion
      if (pulsacion != 0) //Si el valor es 0 es que no se ha pulsado ninguna tecla
        { // descartamos almohadilla y asterisco
          if (pulsacion != '#' && pulsacion != '*' && clave==0)
           { lcd.print(pulsacion); // imprimimos pulsacion
             cursor++;             // incrementamos el cursor
             tone(buzzer,350);     // tono de pulsacion
             delay(200);
             noTone(buzzer);

      //--- Condicionales para comprobar la clave introducida -----------
      // comparamos entrada con cada uno de los digitos, uno a uno
      if (pulsacion == codigoSecreto[posicion]){
          posicion ++; // aumentamos posicion si es correcto el digito
      }

      if (pulsacion == codigoSecreto2[posicion2]){
          posicion2 ++; // aumentamos posicion si es correcto el digito
      }
      
      if (posicion == 8)
       {  


           lcd.setCursor(0,0);      // situamos el cursor el la pos 0 de la linea 0.
           lcd.print("Clave correcta   ");         // escribimos en LCD
           delay(200);                           // tono de clave correcta
           tone(buzzer,500);
           delay(100);
           noTone(buzzer);
           tone(buzzer,600);
           delay(100);
           noTone(buzzer);
           tone(buzzer,800);
           delay(100);
           noTone(buzzer);
  
           lcd.setCursor(0,1); // cursor en la posicion 5, linea 1
           clave=0; // indicamos que se ha introducido la clave

           cursor = 0;
           
           delay(2000);
  
           lcd.setCursor(0,0);      // situamos el cursor el la pos 0 de la linea 0.
           lcd.print("Acceso permitido   ");         // escribimos en LCD    
           lcd.setCursor(0,1);
           lcd.print("         ");       // borramos la clave de la pantalla
           lcd.setCursor(0,1);
           digitalWrite(puerta, LOW); // abrimos puerta


           delay(5000);
           lcd.setCursor(0,0);      // situamos el cursor el la pos 0 de la linea 0.
           lcd.print("Introduzca clave");         // escribimos en LCD   
           lcd.setCursor(0,1);

           posicion=0;
           posicion2=0;

           
          

       }
          
        if(posicion2 == 8) {
           lcd.setCursor(0,0);      // situamos el cursor el la pos 0 de la linea 0.
           lcd.print("Clave correcta   ");         // escribimos en LCD
           delay(200);                           // tono de clave correcta
           tone(buzzer,500);
           delay(100);
           noTone(buzzer);
           tone(buzzer,600);
           delay(100);
           noTone(buzzer);
           tone(buzzer,800);
           delay(100);
           noTone(buzzer);
  
           lcd.setCursor(0,1); // cursor en la posicion 5, linea 1
           clave=0; // indicamos que se ha introducido la clave

           cursor = 0;
           
           delay(2000);
  
           lcd.setCursor(0,0);      // situamos el cursor el la pos 0 de la linea 0.
           lcd.print("Acceso permitido   ");         // escribimos en LCD    
           lcd.setCursor(0,1);
           lcd.print("         ");       // borramos la clave de la pantalla
           lcd.setCursor(0,1);
           digitalWrite(puerta2, LOW); // abrimos puerta
           delay(5000);
           lcd.setCursor(0,0);      // situamos el cursor el la pos 0 de la linea 0.
           lcd.print("Introduzca clave");         // escribimos en LCD   
           lcd.setCursor(0,1);

           posicion=0;
           posicion2=0;
                 
        }
         
     }
     //--- En el caso de que este incompleta o no hayamos acertado ----------
     if(cursor>7)        // comprobamos que no pase de la cuarta posicion
       {   cursor=0;     // lo volvemos a colocar al inicio
           posicion=0;           // borramos clave introducida
           posicion2=0;
           lcd.setCursor(0,1);
           lcd.print(" ");       // borramos la clave de la pantalla
           lcd.print(" ");       // borramos la clave de la pantalla
           lcd.print(" ");       // borramos la clave de la pantalla
           lcd.print(" ");       // borramos la clave de la pantalla
           lcd.print(" ");       // borramos la clave de la pantalla
           lcd.print(" ");       // borramos la clave de la pantalla
           lcd.print(" ");       // borramos la clave de la pantalla
           lcd.print(" ");       // borramos la clave de la pantalla
           lcd.print(" ");       // borramos la clave de la pantalla
           
           if(clave2==0){
             lcd.setCursor(0,0);
            lcd.print("Clave Incorrecta");
           }
           
           if(clave==0 && clave2==0)         // comprobamos que no hemos acertado
              { tone(buzzer,70,500); // para generar
                delay(250); // tono de error
                noTone(buzzer);
              }
          
          delay(3000);
          lcd.setCursor(0,0);     // situamos el cursor el la posición 2 de la linea 0.
          lcd.print("Introduzca clave"); // escribimos en LCD
          lcd.setCursor(0,1);

             
        }
     
    

 //--- Condicionales para encender o apagar el LCD --------------
 if (pulsacion == '#' && luz==0)
     { // comprobamos tecla y encendemos si esta apagado
       lcd.backlight(); // encendemos
       luz=1; // indicamos que esta encendida
       pulsacion =0; // borramos el valor para poder leer el siguiente condicional
     }

 if (pulsacion == '#' && luz==1)
     { // comprobamos tecla y estado
  /*     lcd.noBacklight(); // apagamos
       luz=0; // indicamos que esta apagada*/
     }

 //--- Condicionales para resetear clave introducida -------------
 /*if (pulsacion == '*')
     { // asterisco para resetear el contador
       posicion = 0;
       cursor = 0;
       clave=0;
       posicion=0;
       lcd.setCursor(0,0); // situamos el cursor el la posición 2 de la linea 0.
       lcd.print("Introduzca clave"); // escribimos en LCD
       lcd.setCursor(0,1);
       lcd.print(" "); // borramos de la pantalla los numeros
       lcd.setCursor(0,1);
    
       digitalWrite(ledRojo,HIGH); // encendemos el LED rojo
       digitalWrite(ledVerde, LOW); // apagamos el verde
    }*/
 }
 }
