                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           /* MAIN EL RITO
 * 25/4/18
 * 
 * MEGA CON ETHERNET SHIELD, IR, I2C DISPLAY
 * CREA SERVER EN IP ESTABLECIDA
 * 
 * 
 * 
 * 0.1 alpha
 */

///////////INCLUDES///////////
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <Ethernet.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
////DEFINES ESTRUCTURALES/////
#define NULO  0
#define BOTON 1
#define IMAN  1
#define ETH   2
#define ANA   3
#define OPE   4
////DEFINES EDITABLES ////////
#define RX_ADF  2
#define TX_ADF  3
#define BOTON_RESET 8
#define BOTON_NEXT  7
/////////EDITABLE/////////////
const int NUM_PASOS = 9;
const int TIPO_PASOS [NUM_PASOS] = { IMAN , IMAN  , IMAN , ETH , ANA , ETH , IMAN , OPE , IMAN}; // 0 nulo, 1 boton o iman, 2 ethernet, 3 analog
const int PASOS_SIMULTANEOS [NUM_PASOS] = {0,1,0,0,0,0,0,0,0}; //indica si hay si hay pasos simultaneos y cuantos 
const int NUM_ETH_CORE = 6;
const int NUM_ETH_EXTRA = 1;
const int RELE_NUM = 14;
const int RELE_POS [RELE_NUM] = {22,23,24,25,26,27,28,29,30,31,32,33,34,35};
const int SENSORES_NUM = 5;
const int SENSORES_POS [SENSORES_NUM] = {36,37,38,39,40}; //pines donde se encuentran los sensores, 0 en posicion donde no 
const int SENSORES_PULL [SENSORES_NUM] = {HIGH , HIGH , HIGH, HIGH, HIGH};
const boolean HOW_TO_CHECK [SENSORES_NUM] = {0 , 0 , 1 , 0 , 0}; //true en estado bajo o alto? (0 o 1)
const String MENSAJES_LCD [] { //Los primeros 3 estan reservados
  
  "Bienvenido a    ",//Mensaje de Bienvenida
  "El rito         ",//Nombre del juego
  "Ordenando       ",//Ordenando
  "Listo           ",//fin de orden 
  "1:Perchero/Banco",
  "2:Perchero      ", 
  "2:Banco         ",
  "3:Computadora   ",
  "4:Acceso morge  ",
  "5:Revelador     ", 
  "6:Rompecabezas  ",
  "7:Altar mano    ",
  "8:Altar final   ",
  "JUEGO FINALIZADO", 
};
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
IPAddress ip(192, 168, 0, 101);
EthernetServer server = EthernetServer(23);
const int NUM_J_LINE = 0;
const int PASO_ANA = 4;
/////////NO EDITABLES////////
boolean estado_act [NUM_PASOS];   //array para los pasos resueltos
int sensores_act [SENSORES_NUM];  //array para estado actual de sensores
int sensores_check_lugar[NUM_PASOS];  //array ficticio para salvar simultaneidad
boolean paso_virgen [NUM_PASOS];  //array para saber si es la primera vez que se resuelve el paso
const int DS = 20;                //delay de sensorea
int cursor = 0;                   //cursor para lcd
int mensaje_actual = 0;           //mensaje actual
boolean lcd_change = false;       //actualizar mensaje lcd
boolean hour_change = false;      //actualizar hora lcd
boolean orden_change = false;     //actualiza orden lcd
String hour;                      //hora actual
int tiempo_restante = 3600;       //tiempo restante de juego
unsigned long contador_tiempo = 0;//para el tiempo
unsigned long contador = 0;       //para el tiempo
int paso = 0;                     //estado del game
const char RESET = 'R';           //para avisar reset
const int UPD_ETH = 500;         //tiempo para update eth
boolean play = false;             //jugando o ordenando
int ir_uni = 0;                   //para saltear pasos por ir
int ir_dec = 0;                   //''
boolean ir_change = false;        //''
boolean er_ir_lcd = false;        //''
boolean lcd_start = false;        //para borrar pantalla de abajo al iniciar
boolean resuelto = false;         //si se gano el juego
boolean ret_next = false;
boolean ret_reset = false;
boolean saltea = false;boolean first_orden=true;
//////////CHOCLOS///////////
LiquidCrystal_I2C lcd(0x27, 16,2);                  //lcd
IPAddress myDns(192,168,0, 1);                      //eth
IPAddress gateway(192, 168, 0, 1);                  //eth
IPAddress subnet(255, 255, 0, 0);                   //eth
SoftwareSerial mySoftwareSerial(RX_ADF, TX_ADF);    // RX, TX
DFRobotDFPlayerMini myDFPlayer;                     //dfplayer
void printDetail(uint8_t type, int value);          //dfplayer
//GLOVALES PROPIAS ANALOG
unsigned long contador_ultra = 0;
const int ULTRA_TIM = 200;
int ppromedio[]={1024,1024,1024,1024,1024};
unsigned long contador_parp = 0;       //para el tiempo  
int estado_parp = 0;
const int LIMIT_PARP = 100;
///////////SETUP/////////////
void setup() 
{
  delay(1000);                                                   //delay inicial
  Serial.begin(9600);                                            //init serie
  lcd.begin();                                                   //init LCD
  if (Ethernet.begin(mac) == 0) {                                //pide ip por dhcp
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip, myDns, gateway, subnet);
  }
  server.begin();                                                //inicia server
  mySoftwareSerial.begin(9600);
  Serial.println("INICIANDO");
  if (!myDFPlayer.begin(mySoftwareSerial)) {                     //Arranca dfplayer
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    Serial.println(myDFPlayer.readState()); //read mp3 state
    Serial.println(myDFPlayer.readFileCounts()); //read all file counts in SD card
  }
  llena_arrays(); //llena los arrays de inicio
  dec_sensores_reles();//declara sensores y reles
  lcd.setCursor(0,0); //muestra mensaje de bienvenida
  lcd.print(MENSAJES_LCD[0]);
  lcd.setCursor(0,1);
  lcd.print(MENSAJES_LCD[1]);
  digitalWrite(34, LOW);
  digitalWrite(35, LOW);
  pinMode(A8 , INPUT);
  pinMode(BOTON_RESET , INPUT);
  digitalWrite(BOTON_RESET , HIGH);
  pinMode(BOTON_NEXT , INPUT);
  digitalWrite(BOTON_NEXT , HIGH);
  pinMode(RELE_POS[9] , OUTPUT);
  digitalWrite(RELE_POS[9],LOW);
}
////////////LOOP//////////////
void loop() 
{
  IR();
  LCD();
  eth_update();
  if(play){
    reloj();
    parpadeo();
    secuenciar();   
    }
}

//////////FUNCIONES ESTRUCTURALES////////////////
//actualiza ethernet, usa client_read
void eth_update()
{ 
  if ((millis() - contador) >= UPD_ETH) {
    if(play){ 
      if(PASOS_SIMULTANEOS[paso] == 0){server.write(paso+48);client_read();}
      else{
        int sim = PASOS_SIMULTANEOS[paso];
        int cont = 0;
        while(cont <= sim){
          if(estado_act[paso+cont] == false){server.write(paso+cont+48);client_read();}
          cont++;  
        }
      }
    }else{server.write(RESET);client_read();if(first_orden){delay(1000);digitalWrite(RELE_POS[9] , HIGH); delay(1000);digitalWrite(RELE_POS[9] , LOW);first_orden=false;}}
    contador = millis();
  }
}
//lee el cliente y procesa
void client_read()
{
  EthernetClient client = server.available();
  if (client) {
    char c = client.read();
    while (c != -1){
      Serial.println(c);
      int a = 0;
      while((a-1) < PASOS_SIMULTANEOS[paso]){if((c-48) == paso+a){set_paso(c-48);}a++;}
      c = -1;}
    }
}

//declara sensores y reles
void dec_sensores_reles ()
{
  int a = 0;
  while(a < SENSORES_NUM){
    pinMode(SENSORES_POS[a] , INPUT);
    digitalWrite(SENSORES_POS[a] , SENSORES_PULL[a]);
    a++;
    }
  a = 0;
  while(a < RELE_NUM){
    if(a != 9){
    pinMode(RELE_POS[a] , OUTPUT);
    digitalWrite(RELE_POS[a] , HIGH);}
    a++;
    }
}
//actualiza pasos
void set_paso (int Paso){
  estado_act[Paso] = true;
  }
//comprueba el estado de un sensor
boolean check (boolean cual, int entrada, int ds)
{
  boolean resu = false;
  int contador = 0;  
  if(cual){ while(digitalRead(entrada) == 1 && resu == false){/*delay(ds);*/contador++;if(contador == 50){resu = true;}}
  }else{    while(digitalRead(entrada) == 0 && resu == false){/*delay(ds);*/contador++;if(contador == 50){resu = true;}}}  
  return resu; 
}
//comprueba el estado de todos los sensores, utiliza check
void sensorea()
{
  int a = 0;
  while(a < SENSORES_NUM){
  sensores_act[a] = check(HOW_TO_CHECK[a] , SENSORES_POS[a] , DS);
  a++;
  }
  //analog();
}
//comprueba estado sensores analogicos
int analog()
{
  int a = 4;
  int promedio = 0;
  while(a > 0){ppromedio[a] = ppromedio[a-1];promedio = promedio + ppromedio[a];a--;}
  ppromedio[0]=analogRead(A8);
  promedio = promedio + ppromedio[0];
  promedio = promedio / 5;//Serial.print("Analog");Serial.print(ppromedio[0]);Serial.print("  prom:");Serial.println(promedio);
  return promedio;
}
//recive y procesa el ir
void IR (){
  if(check(0,BOTON_RESET,DS)){delay(500);if(play){reset();}else{play = true;lcd_change=true;mensaje_actual = 3;}}
  if(check(0,BOTON_NEXT,DS)){saltea = true;delay(500);}
 /*   boolean cambio = false;
    boolean borrar = false;
    int num = -1;
    if (irrecv.decode(&results)) {
      if(results.value == 553536955  || results.value == 16761405){Serial.println("play");play = true;lcd_change=true;mensaje_actual = 3;};
      if(results.value == 3855596927 || results.value == 16748655){/*Serial.println("EQ");reset();};
      if(results.value == 2747854299 || results.value == 16754775){/*Serial.println("vol+");};
      if(results.value == 4034314555 || results.value == 16769055){/*Serial.println("vol-");};
      if(results.value == 3810010651 || results.value == 16753245){/*Serial.println("CH-");borrar = true;};
      if(results.value == 5316027    || results.value == 16736925)   {/*Serial.println("CH");}cambio = true;};
      if(results.value == 4001918335 || results.value == 16769565){/*Serial.println("CH+");};
      if(results.value == 2534850111 || results.value == 16724175){/*Serial.println("1");num = 1;};
      if(results.value == 1033561079 || results.value == 16718055){/*Serial.println("2");num = 2;};
      if(results.value == 1635910171 || results.value == 16743045){/*Serial.println("3");num = 3;};
      if(results.value == 2351064443 || results.value == 16716015){/*Serial.println("4");num = 4;};
      if(results.value == 1217346747 || results.value == 16726215){/*Serial.println("5");num = 5;};
      if(results.value == 71952287   || results.value == 16734885)  {/*Serial.println("6");num = 6;};
      if(results.value == 851901943  || results.value == 16728765) {/*Serial.println("7");num = 7;};
      if(results.value == 465573243  || results.value == 16730805) {/*Serial.println("8");num = 8;};
      if(results.value == 1053031451 || results.value == 16732845){/*Serial.println("9");num = 9;};
      if(results.value == 3238126971 || results.value == 16738455){/*Serial.println("0");num = 0;};
      irrecv.resume(); // empezamos una nueva recepción*/
/*  } 
  if(num != -1 && play){ir_dec=ir_uni; ir_uni = num;ir_change=true;}
  if(cambio && play){set_paso(ir_uni+ir_dec*10);borrar=true;}
  if(borrar && play){er_ir_lcd = true; ir_dec = 0; ir_uni = 0;ir_change=true;}*/
}
//recive y procesa el lcd
void LCD () 
{
  if(lcd_change){
      lcd.setCursor(0,0);
      lcd.print(MENSAJES_LCD[mensaje_actual]);
      lcd_change = false;
      if(resuelto){lcd.setCursor(0,1);lcd.print("                ");lcd.setCursor(0,1);lcd.print(hour);}
    }
  if(hour_change){
      lcd.setCursor(9,1);
      lcd.print(hour);
      hour_change = false;
    }
  if(ir_change){
    if(er_ir_lcd){
      lcd.setCursor(0,1);
      lcd.print("             ");
      er_ir_lcd = false;
      ir_change = false;
      }
    else{
      char num [2]= {48 + ir_dec,48 + ir_uni};
      String prnt = num;
      lcd.setCursor(0,1);
      lcd.print(prnt);    
      ir_change = false;
      }
    }
  if(orden_change){
      lcd.setCursor(0,0);
      lcd.print(MENSAJES_LCD[2]);
      lcd.setCursor(0,1);
      lcd.print(MENSAJES_LCD[1]);
      orden_change = false;      
    }
    if(lcd_start){
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd_start = false;      
    }
}
//reloj
void reloj()
{
  if ((millis() - contador_tiempo) >= 1000 && resuelto == false && paso > 0) {        //
     contador_tiempo = millis();
     if(tiempo_restante != 0){
        tiempo_restante = tiempo_restante - 1;
     }
     int min_sex = tiempo_restante / 60;
     int seg_sex = tiempo_restante - min_sex*60;
     int min_dec = min_sex/10;
     int min_uni = min_sex-min_dec*10;
     int seg_dec = seg_sex/10;
     int seg_uni = seg_sex-seg_dec*10;
     char toString[5];
     toString[0]=min_dec + 48;
     toString[1]=min_uni + 48;
     toString[2]=':';
     toString[3]=seg_dec + 48;
     toString[4]=seg_uni + 48;
     hour = toString;
     hour_change = true;
  }  
}
//llena arrays iniciales
void llena_arrays ()
{
  int a = 0;
  while(a < NUM_PASOS){
    estado_act [a] = false;
    a++;
  }
  a = 0;
  while(a < NUM_PASOS){
    paso_virgen [a] = true;
    a++;
  }
  a = 0;
  int b = 0;
  while(a < NUM_PASOS){
    if(TIPO_PASOS[a] == IMAN){
      sensores_check_lugar[a] = b ;
      b++;}
    else{sensores_check_lugar[a] = -1;}
    a++;
  }
  set_paso(3);
}
//checkea si se resolvieron los pasos simultaneos
boolean sim_check (int sim)
{
  if(sim!=0){
    int total = 0;
    int lugar = 0;
    while(lugar <= sim){
      if(paso_virgen[lugar+paso] == false){total++;}
        lugar++;
    }
    if(total == sim+1){return true;}
    else{return false;}}
  else{return false;}
}
//resuelve imanes
void paso_imanes (int paso)
{
  if(TIPO_PASOS[paso] == IMAN){
    int a = sensores_check_lugar[paso]; 
    if(check(HOW_TO_CHECK[a] , SENSORES_POS[a] , DS) == true){
        set_paso(paso);
      }
    }
}
//resetea
void reset()
{
  llena_arrays();
  dec_sensores_reles ();
  play = false;
  paso = 0;
  orden_change = true;
  tiempo_restante = 3600;
  resuelto = false;
  digitalWrite(34, LOW);
  digitalWrite(35, LOW);
  myDFPlayer.pause();
  digitalWrite(RELE_POS[9],HIGH);
  delay(2000);
  digitalWrite(RELE_POS[9],LOW);
}
/////////FUNCION EDITABLE//////////////
//secuencia usa sim_check
void secuenciar()
{
  if(play){
    int sim = PASOS_SIMULTANEOS[paso];
    int act = 0;
    while(act <= sim){ 
      paso_imanes(paso+act);
      if (paso+act == PASO_ANA){if(analog() < 50){set_paso(PASO_ANA);}}
      if(estado_act[paso+act]){
        switch(paso+act){
      
          case 0:
            if(paso_virgen[paso+act]){   
              paso_virgen[paso+act] = false;
              paso++;
              mensaje_actual = 4;
              lcd_change = true;
              lcd_start = true;
              //ACA VA LO QUE CAMBIA EL PASO , RELES ETC, RECORDAR HACER PASO++ EN EL MOMENTO INDICADO
              digitalWrite(RELE_POS[0],LOW);
              myDFPlayer.loop(1);
              if(sim_check(sim)){
                //ACA VA LO QUE CAMBIA LA SIMULTANEIDAD
                }
              }
            break;
    
          case 1:
            if(paso_virgen[paso+act]){    
              paso_virgen[paso+act] = false;
              mensaje_actual = 6;
              lcd_change = true;
              //ACA VA LO QUE CAMBIA EL PASO
              digitalWrite(RELE_POS[1],LOW);
              if(sim_check(sim)){
                //ACA VA LO QUE CAMBIA LA SIMULTANEIDAD
                paso++;
                paso++;
                mensaje_actual = 7;
                lcd_change = true;
                }
              }
            break;
            
          case 2:
            if(paso_virgen[paso+act]){    
              paso_virgen[paso+act] = false;
              mensaje_actual = 5;
              lcd_change = true;
              //ACA VA LO QUE CAMBIA EL PASO
              digitalWrite(RELE_POS[2],LOW);
              if(sim_check(sim)){
                //ACA VA LO QUE CAMBIA LA SIMULTANEIDAD
                paso++;
                paso++;
                mensaje_actual = 7;
                lcd_change = true;
                }
              }
            break; 
              
          case 3:
            if(paso_virgen[paso+act]){    
              paso_virgen[paso+act] = false;
              mensaje_actual = 8;
              lcd_change = true;
              //ACA VA LO QUE CAMBIA EL PASO
              paso++;
              if(sim_check(sim)){
                //ACA VA LO QUE CAMBIA LA SIMULTANEIDAD
                }
              }
            break;
            
          case 4:
            if(paso_virgen[paso+act]){    
              paso_virgen[paso+act] = false;
              mensaje_actual = 9;
              lcd_change = true;
              //ACA VA LO QUE CAMBIA EL PASO
              digitalWrite(RELE_POS[3],LOW);
              myDFPlayer.pause();
              myDFPlayer.loop(2);
              paso++;
              if(sim_check(sim)){
                //ACA VA LO QUE CAMBIA LA SIMULTANEIDAD
                }
              }
            break;    

          case 5:
            if(paso_virgen[paso+act]){    
              paso_virgen[paso+act] = false;
              mensaje_actual = 10;
              lcd_change = true;
              //ACA VA LO QUE CAMBIA EL PASO
              paso++;
              if(sim_check(sim)){
                //ACA VA LO QUE CAMBIA LA SIMULTANEIDAD
                mensaje_actual = 7;
                lcd_change = true;
                }
              }
            break; 
              
          case 6:
            if(paso_virgen[paso+act]){    
              paso_virgen[paso+act] = false;
              mensaje_actual = 11;
              lcd_change = true;
              //ACA VA LO QUE CAMBIA EL PASO
              paso++;
              digitalWrite(RELE_POS[4],LOW);
              myDFPlayer.pause();
              myDFPlayer.loop(3);
              if(sim_check(sim)){
                //ACA VA LO QUE CAMBIA LA SIMULTANEIDAD
                }
              }
            break;

            case 7:
              if(paso_virgen[paso+act]){    
                paso_virgen[paso+act] = false;
                mensaje_actual = 12;
                lcd_change = true;
              //ACA VA LO QUE CAMBIA EL PASO
                paso++;
                digitalWrite(RELE_POS[6],LOW);
                if(sim_check(sim)){
                //ACA VA LO QUE CAMBIA LA SIMULTANEIDAD
                }
              }
            break;
            
          case 8:
            if(paso_virgen[paso+act]){    
              paso_virgen[paso+act] = false;
              mensaje_actual = 13;
              lcd_change = true;
              //ACA VA LO QUE CAMBIA EL PASO
              digitalWrite(RELE_POS[8],LOW);
              myDFPlayer.pause();
              myDFPlayer.play(4);
              delay(10000);
              digitalWrite(RELE_POS[5],LOW);              
              resuelto = true;
              if(sim_check(sim)){
                //ACA VA LO QUE CAMBIA LA SIMULTANEIDAD
                }
              }
            break;
        }
      }else{if(saltea){set_paso(paso+act);saltea=false;}}
    act++;
    
    }
  }    
}

void parpadeo()
{
  if(paso > 0 && paso < 7){
    int a = 0;
    if (paso == 1 || paso == 2 || paso == 6 ){a = 10;}else {a = 10;}
    if((millis() - contador_parp) > a){
      estado_parp++;//Serial.print("Parpadeo: ");Serial.println(estado_parp);
      if(estado_parp == LIMIT_PARP){estado_parp = 0;}
      if(estado_parp > 0 && estado_parp < 10){digitalWrite(35,HIGH);digitalWrite(34,HIGH);}
      if(estado_parp > 10 && estado_parp < 20){digitalWrite(35,HIGH);digitalWrite(34,LOW);}
      if(estado_parp > 20 && estado_parp < 30){digitalWrite(35,LOW);digitalWrite(34,LOW);}
      if(estado_parp > 30 && estado_parp < 40){digitalWrite(35,HIGH);digitalWrite(34,HIGH);}
      if(estado_parp > 40 && estado_parp < 50){digitalWrite(35,HIGH);digitalWrite(34,LOW);}
      if(estado_parp > 50 && estado_parp < 60){digitalWrite(35,LOW);digitalWrite(34,HIGH);}
      if(estado_parp > 60 && estado_parp < 70){digitalWrite(35,LOW);digitalWrite(34,HIGH);}
      if(estado_parp > 70 && estado_parp < 80){digitalWrite(35,LOW);digitalWrite(34,LOW);}
      if(estado_parp > 80 && estado_parp < 90){digitalWrite(35,LOW);digitalWrite(34,HIGH);}
      if(estado_parp > 90 && estado_parp < 100){digitalWrite(35,HIGH);digitalWrite(34,LOW);}
      contador_parp = millis();
    }
  }
  if(paso == 7){digitalWrite(35,HIGH);digitalWrite(34,HIGH);}
}
