/* LAVARROPAS
 * 25/6/18
 * 
 * UNO CON ETHERNET SHIELD, SE CONECTA
 * A SERVER CON IP ESTABLECIDA
 * Y HACE COSAS
 * 
 * 
 * 1.0 alpha
 */
/////////INCLUDES////////////
#include <Ethernet.h>
#include <SPI.h>
//////////DEFINES EDITABLES////////////
#define BOTON 2
#define LED   3
#define LIM0  1023
#define LIM1  230
#define CHANGUI 50
//////////EDITABLES//////////
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x11 };        //diferente en todos los devices, programable en router
byte ip[] = { 192, 168, 0, 111};                            //101 es el server
byte server[] = { 192, 168, 0, 110};                    
const char  PASO_ACTIVACION = '2';
const char  PASO_RESOLUCION = '2';
const char  RESPUESTA = '2';
const char  RESET = 'R';
//////////NO EDITABLES///////
unsigned long contador = 0;
boolean activo = false;
boolean resuelto = false;
boolean reset = false;
boolean reposo = false;
boolean eth_on = false;
boolean first_time_activo = true;
boolean first_time_resuelto = true;
////////CHOCLO///////////////
EthernetClient client;
//GLOBALES PRIVADAS
int ppromedio0[]={1024,1024,1024,1024,1024};
int ppromedio1[]={1024,1024,1024,1024,1024};
boolean flag = false;
boolean flag1 = false;
////////SETUP////////////////
void setup() {
  delay(1000);                                                  //delay inicial
  Serial.begin(9600);                                           //serial
  if (Ethernet.begin(mac) == 0) {                               //I
    Serial.println("Failed to configure Ethernet using DHCP");  //N
  }                                                             //T
  printIPAddress();                                                          
///////////////SETUP EDITABLE//////////////////////
pinMode(A0 , INPUT);
pinMode(A1 , INPUT);
pinMode(BOTON , INPUT);
digitalWrite(BOTON , HIGH);
pinMode(LED, OUTPUT);
//////////////////////////////////////////////////
}
/////////////////////LOOP/////////////////////////
void loop() {
  eth_update();
  if_reset();
  if_reposo();
  if_activo();
  if_resuelto();//Serial.print("UNO: ");Serial.println(analog0());Serial.print("DOS: ");Serial.println(analog1());//Serial.print("BOT: ");Serial.println(digitalRead(BOTON));
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
      if (client.connect("192.168.0.110", 24)){eth_on = true;}else{}
      }else{
        char c = client.read();
        while(c != -1){
          if(c == PASO_ACTIVACION && resuelto == false){activo = true; reposo = false;}
          if(c == RESET && reposo == false){reset = true; activo = false; resuelto = false; reposo = false;}
          if(c == PASO_RESOLUCION){if(resuelto){client.write(RESPUESTA);}}
          Serial.println(c);
          c = client.read();
          eth_on = false;c=-1;
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
    first_time_activo = true;
    first_time_resuelto = true;
    //EDITAR A COSAS A RESETEAR
  }
}
//reposo
void if_reposo()
{
  if(reposo){
   /////////EDITAR COSAS A HACER EN REPOSO////
    
    }
}
//activo
void if_activo()
{
  if(activo){
  ////////EDITAR A COSAS A HACER CUANDO SE ACTIVA/////
  
  if(analog0()>LIM0-CHANGUI && analog0()<LIM0+CHANGUI /*&& analog1()>LIM1-CHANGUI && analog1()<LIM1+CHANGUI*/ && digitalRead(BOTON)==0){ 
    resuelto = true; activo = false;}
    if(first_time_activo){
      first_time_activo = false;
      //EDITAR A COSAS A HACER LA PRIMERA VEZ QUE SE ACTIVA//
    }
  }
}
//resuelto
void if_resuelto()
{
  if(resuelto){
  /////////EDITAR COSAS A HACER RESUELTO//////
    if(first_time_resuelto){
      first_time_resuelto = false;
      //EDITAR A COSAS A HACER LA PRIMERA VEZ
      }
    }
}

//FUNCONES ESPECIFICAS
int analog0()
{
  int a = 4;
  int promedio = 0;
  while(a > 0){ppromedio0[a] = ppromedio0[a-1];promedio = promedio + ppromedio0[a];a--;}
  ppromedio0[0]=analogRead(A0);
  promedio = promedio + ppromedio0[0];
  promedio = promedio / 5;
  return promedio;
}

int analog1()
{
  int a = 4;
  int promedio = 0;
  while(a > 0){ppromedio1[a] = ppromedio1[a-1];promedio = promedio + ppromedio1[a];a--;}
  ppromedio1[0]=analogRead(A1);
  promedio = promedio + ppromedio1[0];
  promedio = promedio / 5;
  return promedio;
}
