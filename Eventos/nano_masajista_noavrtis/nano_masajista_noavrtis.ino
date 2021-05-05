/* LUCES_PANEL_04_05_XX
 * 
 * MEGA, BOTONES, RELE, y RGB
 * 
 */
 
//INCLUDES

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//CONSTANTES

#define NUMPASOS        30
#define N_BOTONES         4
#define TIEMPO_PRENDIDO 250
 
//EDITABLE
#define SPRINT      false
#define NEED_REPOSO false
#define LUZ1    8
#define LUZ2    9
#define LUZ3    10
#define LUZ4    11
#define BOT1    4
#define BOT2    5
#define BOT3    6
#define BOT4    7
#define BUZZ    3
#define RESET   2
#define RANDOM  A0

#define DS  15

#define VELOCIDAD 10

const int N_INPUTS = 5;
const int INPUTS[N_INPUTS] = {BOT1,BOT2,BOT3,BOT4,RESET};
const int INPUTS_ISTATE[N_INPUTS] = {1,1,1,1,1};
const int N_OUTPUTS = 5;
const int OUTPUTS[N_OUTPUTS] = {LUZ1, LUZ2, LUZ3, LUZ4, BUZZ};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {0,0,0,0,0};

//GLOBALES
LiquidCrystal_I2C lcd(0x3f, 16,2); //3F,27
int cursor = 0;      // posicion inicial de la clave en el LCD
int paso = 0;
int respuesta[NUMPASOS];
boolean animacion = false;
boolean win = true;
const int LUCES[N_BOTONES]= {LUZ1, LUZ2, LUZ3, LUZ4};
const int BOTONES[N_BOTONES] = {BOT1,BOT2,BOT3,BOT4};
const int TONOS[N_BOTONES] = {440,550,660,770};
const String LCD_STRUCTURE1 = "RECORD       00%";
const String LCD_STRUCTURE2 = "ACTUAL       00%";
const String LCD_WIN1 = "     GANADOR    ";
const String LCD_WIN2 = "JUEGOS MENTALES ";
const int LCDPOS1 = 13;
const int LCDPOS2 = 13;
int actual = 0;
int porcentaje = 0;
int porcentaje_record = 0;
//NO EDITABLE
boolean reposo = false;
boolean activo = false;
boolean resuelto = false;
unsigned long timer_print = 0;
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
//si necesita reposo
  if(NEED_REPOSO){reposo=true;activo=false;resuelto=false;}else{reposo=false;activo=true;resuelto=false;}
//EDITABLE
  randomSeed(analogRead(RANDOM));
  delay(1000);
  lcd.begin();
  crear_paso(paso);
  delay(100);
  lcd.setCursor(0,0);
  lcd.print(LCD_STRUCTURE1);
  lcd.setCursor(0,1);
  lcd.print(LCD_STRUCTURE2);
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
  }
}

void if_activo()
{
  if(activo){

    if(check(0,RESET,DS)){

      reinicia();
      
    }else{
      if(win == false){
          if(animacion){
            lcd_update(paso);
            crear_paso(paso+1);
            delay(1000);
            for(int i = 0;i <= paso+1 ; i++){
              ilumina(respuesta[i]);
              }
            animacion = false;
            paso++;
            }
            
          for(int i = 0; i < N_BOTONES; i++){
            if(check(0,BOTONES[i],DS)){
              ilumina(i);
              if(comprueba(i,actual)){actual++;i = N_BOTONES;}else{error();i=N_BOTONES;}
              if(actual == paso+1){animacion = true;actual = 0;} 
              }     
          }
         if(animacion == true && paso == NUMPASOS){ganaste();animacion = false;}
      }
    }
  }
}

void if_resuelto()
{
  if(resuelto){
  }
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
    Serial.print("Actual: ");
    Serial.println(actual);
    Serial.print("Paso: ");
    Serial.println(paso);
    Serial.print("Respuesta: ");
    Serial.println(respuesta[actual]);    
    }
  }


//NO EDITABLE
//comprueba el estado de un sensor
boolean check (boolean cual, int entrada, int ds)
{
  boolean resu = false;
  int contador = 0;  
  if(cual){ while(digitalRead(entrada) == 1 && resu == false){delay(ds);contador++;if(contador == 5){resu = true;}}
  }else{    while(digitalRead(entrada) == 0 && resu == false){delay(ds);contador++;if(contador == 5){resu = true;}}}  
  return resu; 
}

void crear_paso(int numero)
{
  
  int randNumber = random(0, N_BOTONES);
  respuesta[numero] = randNumber;
}

void ilumina(int lugar)
{

  digitalWrite(LUCES[lugar],HIGH);
  tone(BUZZ,TONOS[lugar]);
  delay(TIEMPO_PRENDIDO);
  digitalWrite(LUCES[lugar],LOW);
  noTone(BUZZ);
  delay(100);
}

void lcd_update(int numero)
{
 if(numero >= 0){
  if(numero < NUMPASOS){

    porcentaje = map(numero+1 , 0, NUMPASOS, 0, 100);
    int dec_por = porcentaje/10;
    int u_por = porcentaje - dec_por*10;
    char dec = dec_por + 48;
    char u = u_por +48;
    lcd.setCursor(LCDPOS2,1);
    lcd.print(dec);
    lcd.setCursor(LCDPOS2+1,1);
    lcd.print(u);
    if(porcentaje > porcentaje_record) {
        porcentaje_record = porcentaje;
        int dec_por = porcentaje/10;
        int u_por = porcentaje - dec_por*10;
        char dec = dec_por + 48;
        char u = u_por +48;
        lcd.setCursor(LCDPOS1,0);
        lcd.print(dec);
        lcd.setCursor(LCDPOS1+1,0);
        lcd.print(u);
        }  
    }
 }else{
  switch(numero){

    case -1:{lcd.setCursor(0,0);
           lcd.print(LCD_STRUCTURE1);
           lcd.setCursor(0,1);
           lcd.print(LCD_STRUCTURE2);break;}
    case -2:{
      if(porcentaje > porcentaje_record){        porcentaje_record = porcentaje;
        int dec_por = porcentaje/10;
        int u_por = porcentaje - dec_por*10;
        char dec = dec_por + 48;
        char u = u_por +48;
        lcd.setCursor(LCDPOS1,0);
        lcd.print(dec);
        lcd.setCursor(LCDPOS1+1,0);
        lcd.print(u);}
        char dec = '0';
        char u = '0';
        lcd.setCursor(LCDPOS2,1);
        lcd.print(dec);
        lcd.setCursor(LCDPOS2+1,1);
        lcd.print(u);
        
      
      break;}
    case -3:{lcd.setCursor(0,0);
           lcd.print(LCD_WIN1);
           lcd.setCursor(0,1);
           lcd.print(LCD_WIN2);break;}
    
    }
 } 
}

void reinicia ()
{
  win = false;
  paso = 0;
  actual = 0;
  animacion = false;
  crear_paso(paso);
  ilumina(respuesta[actual]);
  lcd_update(-1);
  porcentaje = 0;
  porcentaje_record = 0;
}

void error()
{
  delay(200);                           // tono de error
  tone(BUZZ,800);
  delay(100);
  noTone(BUZZ);
  tone(BUZZ,600);
  delay(100);
  noTone(BUZZ);
  tone(BUZZ,500);
  delay(100);
  noTone(BUZZ);
  lcd_update(-2);
  paso = 0;
  actual = 0;
  animacion = false;
  delay(1000);
  crear_paso(paso);
  ilumina(respuesta[actual]);
}

void ganaste(){
  win = true;
  lcd_update(-3);
  delay(200);                           // tono de clave correcta
  tone(BUZZ,500);
  delay(100);
  noTone(BUZZ);
  tone(BUZZ,600);
  delay(100);
  noTone(BUZZ);
  tone(BUZZ,800);
  delay(100);
  }

boolean comprueba(int acomprobar, int actual)
{
  boolean resu = false;
  if(acomprobar == respuesta[actual]){resu = true;}
  return resu;
}
