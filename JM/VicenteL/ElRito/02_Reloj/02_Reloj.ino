/* 02_Reloj
 * 12/5/18
 * 
 * UNO CON ETHERNET SHIELD, SE CONECTA
 * A SERVER CON IP ESTABLECIDA
 * CONTROLA UN PAP Y UN SENSOR DE OBSTACULOS
 * 
 * 
 * 0.1 alpha
 */
/////////INCLUDES////////////
#include <Ethernet.h>
#include <SPI.h>
#include <Stepper.h>
//////////DEFINES////////////
#define tiempo_total 3600
#define start 7
#define steps_by_time 8
//////////EDITABLES//////////
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x02 };        //diferente en todos los devices, programable en router
byte ip[] = { 192, 168, 0, 102};                            //101 es el server
byte server[] = { 192, 168, 0, 101};                    
const char  PASO_ACTIVACION = '1';
const char  PASO_RESOLUCION = 'Z';
const char RESPUESTA = 'Z';
const char RESET = 'R';
const char VUELTA = 'V';
const char TIEMPO = 'T';
boolean first_reset = false;
boolean first_time = true;
//////////NO EDITABLES///////
unsigned long contador = 0;
boolean activo = false;
boolean resuelto = false;
boolean reset = false;
boolean reposo = false;
boolean eth_on = false;
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution

////////CHOCLO///////////////
EthernetClient client;
Stepper myStepper(stepsPerRevolution, 3, 4, 5, 6);
/////GLOBALES EDITABLES//////
unsigned long contador_pap = 0;
unsigned int tiempo_restante = 3600;
unsigned long contador_tiempo = 0;
char toString[5] = {'T','6','0','0','0'};
////////SETUP////////////////
void setup() {
  delay(5000);                                                  //delay inicial
  Serial.begin(9600);                                           //serial
  if (Ethernet.begin(mac) == 0) {                               //I
    Serial.println("Failed to configure Ethernet using DHCP");  //N
  }                                                             //T
  printIPAddress();                                                             //T
///////////////SETUP EDITABLE//////////////////////
  myStepper.setSpeed(100);
  pinMode(start,INPUT);
//////////////////////////////////////////////////
}
/////////////////////LOOP/////////////////////////
void loop() {
  eth_update();
  if_reset();
  if_reposo();
  if_activo();
  if_resuelto();
}
//////////////////////NO EDITABLE/////////////////
//imprime ip
void printIPAddress()
{
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }

  Serial.println();
}
//actualiza eth
void eth_update()
{
  if ((millis() - contador) >= 500) { // Esto lo puedes dejar como estaba, pero creo que es más ilustrativo así
    contador = millis();
    if(eth_on == false){
      if (client.connect("192.168.0.101", 23)){eth_on = true;}
      }else{
        char c = client.read();
        while(c != -1){
          if(c == PASO_ACTIVACION && resuelto == false || c == '2' && resuelto == false || c == '3' && resuelto == false || c == '4' && resuelto == false || c == '5' && resuelto == false || c == '6' && resuelto == false || c == '7' && resuelto == false ){activo = true; reposo = false;}
          if(c == RESET && reposo == false){reset = true; activo = false; resuelto = false; reposo = false;}
          if(c == PASO_RESOLUCION){if(resuelto){/*client.write(RESPUESTA);*/}}
        /*  if(c == 'V'){myStepper.step(-200);while(digitalRead(start)==1){myStepper.step(-1);};myStepper.step(-100);while(digitalRead(start)==1){myStepper.step(1);}}
          if(c == 'W'){myStepper.step(200);while(digitalRead(start)==1){myStepper.step(1);}}*/
          Serial.println(c);
          c = client.read();
          eth_on = false;c = -1;
      }
      if(eth_on == false){client.stop();contador = millis();}
    }
  }
}
//////////////////EDITAR/////////////////
//reset
void if_reset ()
{
  if(reset){
    reset = false;
    reposo = true;
    first_time = true;
    if(digitalRead(start)==1){
      while(digitalRead(start)==1){myStepper.step(-1);}
      myStepper.step(-200);
      while(digitalRead(start)==1){myStepper.step(1);
      first_reset = false;}
    }else{   
      if(first_reset){
        first_reset = false;
        myStepper.step(-200);
        while(digitalRead(start)==1){myStepper.step(-1);}
        myStepper.step(-200);
        while(digitalRead(start)==1){myStepper.step(1);}
        }
    }
    tiempo_restante = 3600;
    contador_pap = millis();
    }
}
//reposo
void if_reposo()
{
  if(reposo){
   /////////EDITAR COSAS A HACER EN REPOSO////
       contador_pap = millis();
    
    }
}
//activo
void if_activo()
{
  if(activo){
  ////////EDITAR A COSAS A HACER CUANDO SE ACTIVA///// 
    if ((millis() - contador_pap) >= /*144000*/14000) {        //
      contador_pap = millis();
      if(digitalRead(start)==1 && first_time==false){
        int z = 0;
        while(z < steps_by_time/*84*/){
          myStepper.step(1);
          z++;
        }
      }
      if(first_time){
        myStepper.step(/*84*/steps_by_time);
        if(digitalRead(start)==1){first_time = false;first_reset = true;}
        }
    }
    if ((millis() - contador_tiempo) >= 1000) {        //
      contador_tiempo = millis();
      Serial.println(tiempo_restante);
      if(tiempo_restante != 0){
        tiempo_restante = tiempo_restante - 1;
      }else{while(digitalRead(start)==1){myStepper.step(1);}}
    }  
  }
}
//resuelto
void if_resuelto()
{
  if(resuelto){
  /////////EDITAR COSAS A HACER RESUELTO//////
    
    }
}

