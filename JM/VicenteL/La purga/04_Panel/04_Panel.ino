/* 04_Tablero
 * 27/6/18
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
#define LLAVE 5
#define LIM0  50
#define LIM1  940
#define LIM2  350
#define LIM3  610
#define CHANGUI 80
//////////EDITABLES//////////
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x14 };        //diferente en todos los devices, programable en router
byte ip[] = { 192, 168, 0, 114};                            //101 es el server
byte server[] = { 192, 168, 0, 110};                    
const char  PASO_ACTIVACION = '3';
const char  PASO_RESOLUCION = '3';
const char  RESPUESTA = '3';
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
int ppromedio2[]={1024,1024,1024,1024,1024};
int ppromedio3[]={1024,1024,1024,1024,1024};
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
pinMode(A2 , INPUT);
pinMode(A3 , INPUT);
pinMode(LLAVE , INPUT);
digitalWrite(LLAVE , HIGH);
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

    if(first_time_activo){
      first_time_activo = false;
      //EDITAR A COSAS A HACER LA PRIMERA VEZ QUE SE ACTIVA//

    }
    boolean pote0 = false;
    boolean pote1 = false;
    boolean pote2 = false;
    boolean pote3 = false;
    boolean linea = false;Serial.println("NUEVA MEDICION");
    if(analog0()>LIM0-CHANGUI && analog0()<LIM0+CHANGUI){pote0=true;}Serial.println(analog0()); 
    if(analog1()>LIM1-CHANGUI && analog1()<LIM1+CHANGUI){pote1=true;}Serial.println(analog1());
    if(analog2()>LIM2-CHANGUI && analog2()<LIM2+CHANGUI){pote2=true;}Serial.println(analog2());
    if(analog3()>LIM3-CHANGUI && analog3()<LIM3+CHANGUI){pote3=true;}Serial.println(analog3());delay(500);
    if(digitalRead(LLAVE) == 0){delay(20); if(digitalRead(LLAVE) == 0){linea = true;}}Serial.print("LLAVE ");Serial.println(digitalRead(LLAVE)); 
    if(pote0 && pote1 && pote2 && pote3 && linea){activo = false; resuelto = true;}
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

int analog2()
{
  int a = 4;
  int promedio = 0;
  while(a > 0){ppromedio2[a] = ppromedio2[a-1];promedio = promedio + ppromedio2[a];a--;}
  ppromedio2[0]=analogRead(A2);
  promedio = promedio + ppromedio2[0];
  promedio = promedio / 5;
  return promedio;
}

int analog3()
{
  int a = 4;
  int promedio = 0;
  while(a > 0){ppromedio3[a] = ppromedio3[a-1];promedio = promedio + ppromedio3[a];a--;}
  ppromedio3[0]=analogRead(A3);
  promedio = promedio + ppromedio3[0];
  promedio = promedio / 5;
  return promedio;
}
