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
  delay(1000);                                                  //delay inicial
  Serial.begin(9600);                                           //serial
  if (Ethernet.begin(mac) == 0) {                               //I
    Serial.println("Failed to configure Ethernet using DHCP");  //N
  }                                                             //T
  printIPAddress();boolean hello = true;while(hello)
  //E
  {
  if (client.connect("192.168.0.101", 23)) {                    //R
    Serial.println("connected");hello=false;                                //N
  } else {                                                      //E
    Serial.println("connection failed");                        //T
  }}                                                             //T
///////////////SETUP EDITABLE//////////////////////
  myStepper.setSpeed(150);
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
//  Serial.println(digitalRead(start));
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
    char c = client.read();
    while(c != -1){
      if(c == PASO_ACTIVACION && resuelto == false){activo = true; reposo = false;}
      if(c == RESET && reposo == false){reset = true; activo = false; resuelto = false; reposo = false;}
      if(c == PASO_RESOLUCION){if(resuelto){/*client.write(RESPUESTA);*/}}
      if(c == 'T'){int_to_string(tiempo_restante);int a=0;while(a<5){client.write(toString[a]);Serial.print(toString[a]);a++;}Serial.println();}
      if(c == 'V'){myStepper.step(-200);while(digitalRead(start)==1){myStepper.step(-1);};myStepper.step(-100);while(digitalRead(start)==1){myStepper.step(1);}}
      if(c == 'W'){myStepper.step(200);while(digitalRead(start)==1){myStepper.step(1);}}
      Serial.println(c);
      c = client.read();
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
    int_to_string(tiempo_restante);
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
        while(z < 8/*84*/){
          myStepper.step(1);
          z++;
        }
      }
      if(first_time){
        myStepper.step(/*84*/8);
        if(digitalRead(start)==1){first_time = false;first_reset = true;}
        }
    }
    if ((millis() - contador_tiempo) >= 1000) {        //
      contador_tiempo = millis();
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

//FUNCIONES ESPECIFICAS
void int_to_string (int convertir) //convierte un int de segundos a un string de hora, 4 numeros
{
 int min_sex = convertir / 60;
 int seg_sex = convertir - min_sex*60;
 int min_dec = min_sex/10;
 int min_uni = min_sex-min_dec*10;
 int seg_dec = seg_sex/10;
 int seg_uni = seg_sex-seg_dec*10;
 toString[1]=min_dec + 48;
 toString[2]=min_uni + 48;
 toString[3]=seg_dec + 48;
 toString[4]=seg_uni + 48;
}
