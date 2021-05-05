//INCLUDES
#include <LiquidCrystal.h>

//GLOBALES
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);
boolean tubo = false;
int IMAN = 6;

//SETUP
void setup() {
  
       lcd.begin(16, 2);           // Fijamos el numero de caracteres y filas
       pinMode( IMAN, INPUT) ; // 
       telefono_colgado();
       tubo = digitalRead(IMAN);
}


//LOOP
void loop() {

  if(digitalRead(IMAN)==0){

    telefono_descolgado();
    
    } else {
      
      telefono_colgado();
      
      }

}

//FUNCIONES

void telefono_colgado() {

  if(tubo == false){
       lcd.setCursor(0,0);
       lcd.print("Descuelgue el");  // Aqi va el mensaje
       lcd.setCursor(0,1);
       lcd.print("telefono");
       tubo = true;
    }
  }

  void telefono_descolgado(){

   if(tubo){
    
       lcd.setCursor(0,0);
       lcd.print("Ingrese numero");  // Aqi va el mensaje
       lcd.setCursor(0,1);
       lcd.print("telefonico");
       tubo = false;
       
      }
    }
