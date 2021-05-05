#include <Keypad.h>
#include <Wire.h> 


int ledPin = 13;      
int buzzerPin = 12;   
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
 
#define Password_Lenght 5
char tecla;
char Master[Password_Lenght] = "4952"; 

char Data[Password_Lenght];
byte data_count = 0, master_count = 0;
bool Pass_is_good;

void setup() {
   Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
   pinMode(buzzerPin, OUTPUT);
  digitalWrite(ledPin, HIGH);  
digitalWrite(buzzerPin, LOW); 
 
}

void loop() {
   
  
  tecla = teclado.getKey();
  if(tecla != NO_KEY){
      Data[data_count] = tecla; // store char into data array
     digitalWrite(buzzerPin, HIGH); 
     delay(500); 
     digitalWrite(buzzerPin, LOW);  
      data_count++; 
      Serial.print(Data);
    
       
        if(data_count==1 && Data[0]!='4'){
           //Serial.print(Data);
           clearData(); 
        }
        if(data_count==2 && Data[1]!='9'){
         // Serial.print(Data);
           clearData(); 
        }
         if(data_count==3 && Data[2]!='5'){
         // Serial.print(Data);
           clearData(); 
        }
         if(data_count==4 && Data[3]!='2'){
         // Serial.print(Data);
           clearData(); 
        }
        
  }
if(data_count == Password_Lenght-1) // if the array index is equal to the number of expected chars, compare data to master
  {
    for(int c=0;  c<5;  c++){
           digitalWrite(buzzerPin, HIGH); 
           delay(100); 
           digitalWrite(buzzerPin, LOW);  
           delay(100); 
        }
    
   

    if(!strcmp(Data, Master)){ // equal to (strcmp(Data, Master) == 0)
      
      digitalWrite(ledPin, LOW);  
       for(int c=0;  c<5;  c++){
           digitalWrite(buzzerPin, HIGH); 
           delay(100); 
           digitalWrite(buzzerPin, LOW);  
           delay(100); 
        }
       delay(10000);// added 1 second delay to make sure the password is completely shown on screen before it gets cleared.
       digitalWrite(ledPin, HIGH);  
       clearData(); 
        
    }
     

    delay(1000);// added 1 second delay to make sure the password is completely shown on screen before it gets cleared.
    
    clearData();   
  }
  
  
}

void clearData()
{
  while(data_count !=0)
  {   // This can be used for any array size, 
    Data[data_count--] = 0; //clear array for new data
  }
  return;
}

