/* 06_LinternaMotor
 * 02/7/18
 * 
 * UNO CON ETHERNET SHIELD, SE CONECTA
 * A SERVER CON IP ESTABLECIDA
 * Y CONTROLA UN RELE Y UN PAP
 * 
 * 
 * 1.0 alpha
 */
/////////INCLUDES////////////
#include <Ethernet.h>
#include <SPI.h>
////////INCLUDES EDITABLES/////////////
#include <Stepper.h>
//////////DEFINES EDITABLES////////////
#define R_LINTERNA  6
#define R_PERSIANA  7
#define S_LINTERNA  8
#define stepsPerRevolution 200
#define MOVIMIENTO  50
//////////EDITABLES//////////
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x16 };        //diferente en todos los devices, programable en router
byte ip[] = { 192, 168, 0, 116};                            //110 es el server
byte server[] = { 192, 168, 0, 110};                    
const char  PASO_ACTIVACION = '8';
const char  PASO_RESOLUCION = 'N';
const char  RESPUESTA = 'N';
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
Stepper myStepper(stepsPerRevolution, 2, 3, 4, 5);
//GLOBALES PRIVADAS
boolean linterna_flag;
boolean derecha;
unsigned long contador_persiana = 0;
const unsigned long TIEMPO_PERSIANA = 180000;
////////SETUP////////////////
void setup() {
  delay(1000);                                                  //delay inicial
  Serial.begin(9600);                                           //serial
  if (Ethernet.begin(mac) == 0) {                               //I
    Serial.println("Failed to configure Ethernet using DHCP");  //N
  }                                                             //T
  printIPAddress();                                                          
///////////////SETUP EDITABLE//////////////////////
  // set the speed at 60 rpm:
  myStepper.setSpeed(15);
  pinMode(R_LINTERNA , OUTPUT);
  pinMode(R_PERSIANA , OUTPUT);
  pinMode(S_LINTERNA , INPUT);
  digitalWrite(R_LINTERNA , HIGH);
  digitalWrite(R_PERSIANA , HIGH);
  digitalWrite(S_LINTERNA , HIGH);
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
          if(c == PASO_RESOLUCION){if(resuelto){/*client.write(RESPUESTA);*/}}
          if(c == '9'){if(linterna_flag){linterna_flag = false; digitalWrite(R_LINTERNA , HIGH);contador_persiana = 0;}}
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
    digitalWrite(R_LINTERNA , HIGH);
    digitalWrite(R_PERSIANA , HIGH);
    unsigned long contador_reset = millis();
    boolean step_play=true;
    while(digitalRead(S_LINTERNA) && step_play){myStepper.step(-1);if((millis() - contador_reset) > 10000){step_play = false;}}
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
      digitalWrite(R_LINTERNA , LOW);
      linterna_flag = true;
      derecha = true;
      contador_persiana = 0;
    }

    if(linterna_flag){
      if (derecha){myStepper.step(MOVIMIENTO);derecha = false;}else{myStepper.step(-MOVIMIENTO);derecha = true;}
      }
    Serial.println(millis() - contador_persiana);
    if((millis() - contador_persiana) > TIEMPO_PERSIANA){
    digitalWrite(R_PERSIANA , LOW); 
    delay(2000); 
    digitalWrite(R_PERSIANA , HIGH);
    contador_persiana = millis();}
    
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
