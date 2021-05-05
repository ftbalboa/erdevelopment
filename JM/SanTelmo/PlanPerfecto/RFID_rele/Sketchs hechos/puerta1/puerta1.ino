#include <MFRC522.h>
#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int buzzer=13;     // pin altavoz    
int puerta=12;    
int level=11;  


int tarjeta=0;

int tarjeta_level=0;
     
const byte filas = 4;
const byte columnas = 4;
byte pinesFilas[filas] = {2,3,4,5};
byte pinesColumnas[columnas] = {6,7,8,9};
char teclas[filas][columnas] = {
     {'1','2','3','A'},
     {'4','5','6','B'},
     {'7','8','9','C'},
     {'*','0','#','D'}
  };
Keypad teclado = Keypad(makeKeymap(teclas),pinesFilas,pinesColumnas,filas,columnas); 
 
#define Password_Lenght 7
char tecla;
char Master[Password_Lenght] = "123456"; 
char Data[Password_Lenght];
byte data_count = 0, master_count = 0;
bool Pass_is_good;

#define Password_Lenght2 7
char tecla2;
char Master2[Password_Lenght2] = "654321"; 
char Data2[Password_Lenght2];
byte data_count2 = 0, master_count2 = 0;
bool Pass_is_good2;

char msj4[] = "Ingrese tarjeta  ";
char msj5[] = "Nivel de seguridad  ";
char msj[] =  "Introduzca clave";
char msj2[] = "Clave correcta   ";
char msj3[] = "Clave Incorrecta  ";

#define RST_PIN         40          // Configurable, see typical pin layout above
#define SS_PIN          53 
MFRC522 mfrc522(SS_PIN, RST_PIN);



void setup() {
 pinMode (buzzer, OUTPUT);
 pinMode (puerta, OUTPUT);
 digitalWrite(puerta, HIGH); // cerramos puerta
 pinMode (level, OUTPUT);
      
 Serial.begin(9600);
 
  SPI.begin();     // Init SPI bus
  delay(500);
  mfrc522.PCD_Init();   // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  
  
  lcd.begin();// initialize the lcd 
  lcd.backlight();

}
int rfid_true(){
    int i = mfrc522.PICC_IsNewCardPresent();
  if ( ! mfrc522.PICC_IsNewCardPresent()){
       
    }
  if(! mfrc522.PICC_ReadCardSerial()) {
      
    }
     return i;   
 }
int get_tarjeta_level(){
   int t= digitalRead(level);
   return t;
  
  }
void loop() {
 tarjeta = rfid_true();
 tarjeta_level = get_tarjeta_level();
//delay(500);  
//Serial.println(tarjeta);
 
if(tarjeta==0){
  
   lcd.setCursor(0,0);
   for(int c=0;  c<16;  c++){
       lcd.print(msj4[c]);
    }
    
}else{
    if(tarjeta_level==1){
         lcd.setCursor(0,0);
         for(int c=0;  c<16;  c++){
            lcd.print(msj[c]);
         }
         



      
     }else{
      lcd.setCursor(0,0);
         for(int c=0;  c<16;  c++){
            lcd.print(msj5[c]);
         }
     }
}
if(tarjeta==1&&tarjeta_level==1){
    
    
  
   lcd.setCursor(0,0);
   for(int c=0;  c<16;  c++){
       lcd.print(msj[c]);
    }
  
  tecla = teclado.getKey();
  if(tecla != NO_KEY){
      Data[data_count] = tecla; // store char into data array
      lcd.setCursor(data_count,1); // move cursor to show each new char
    lcd.print(Data[data_count]); // print char at said cursor
      data_count++; 
        //Serial.print(Data);
         tone(buzzer,350);     // tono de pulsacion
             delay(200);
             noTone(buzzer);
    }
if(data_count == Password_Lenght-1) // if the array index is equal to the number of expected chars, compare data to master
  {
    
    lcd.clear();
    lcd.setCursor(0, 0);
   

    if(!strcmp(Data, Master)){ // equal to (strcmp(Data, Master) == 0)
      lcd.setCursor(0,0);
   for(int c=0;  c<16;  c++){
       lcd.print(msj2[c]);
    }
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
           digitalWrite(puerta, LOW); 
            clearData();  
             delay(10000);
    }else{
      lcd.setCursor(0,0);
   for(int c=0;  c<16;  c++){
       lcd.print(msj3[c]);
    }
      delay(200);                           // tono de clave correcta
         tone(buzzer,800);
         delay(100);
         noTone(buzzer);
         tone(buzzer,600);
         delay(100);
         noTone(buzzer);
         tone(buzzer,500);
         delay(100);
         noTone(buzzer);
    delay(1000);// added 1 second delay to make sure the password is completely shown on screen before it gets cleared.
    lcd.clear();
    clearData();   
  }
    
    
    }

  
 

 

}


tecla2 = teclado.getKey();
  if(tecla2 != NO_KEY){
      Data2[data_count2] = tecla2; // store char into data array
      data_count2++; 
     // Serial.print(Data2);
          tone(buzzer,350);     // tono de pulsacion
             delay(200);
             noTone(buzzer);
    }
if(data_count2 == Password_Lenght2-1) // if the array index is equal to the number of expected chars, compare data to master
  {
   if(!strcmp(Data2, Master2)){ // equal to (strcmp(Data, Master) == 0)
     
           digitalWrite(puerta, HIGH); 
            clearData();  
             
    }else{
       clearData();  
      
      }
    
    }



}
void clearData()
{
  while(data_count !=0)
  {   // This can be used for any array size, 
    Data[data_count--] = 0; //clear array for new data
  }
  while(data_count2 !=0)
  {   // This can be used for any array size, 
    Data2[data_count2--] = 0; //clear array for new data
  }
  
  return;
}

