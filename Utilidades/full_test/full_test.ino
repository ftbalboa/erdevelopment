#include <Servo.h>
#include <MaxMatrix.h>
Servo myservo;  // create servo object to control a servo
int DIN = 7;   // DIN pin of MAX7219 module
int CLK = 5;   // CLK pin of MAX7219 module
int CS = 6;    // CS pin of MAX7219 module
int maxInUse = 0;
int servo=0;
MaxMatrix m1(DIN, CS, CLK, 1);
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output 
char A[] = {4, 8,
            B01111110,
            B00010001,
            B00010001,
            B01111110,
           };
char B[] = {4, 8,
            B01111111,
            B01001001,
            B01001001,
            B00110110,
           };
char smile01[] = {8, 8,
                  B00111100,
                  B01000010,
                  B10010101,
                  B10100001,
                  B10100001,
                  B10010101,
                  B01000010,
                  B00111100
                 };
char smile02[] = {8, 8,
                  B00111100,
                  B01000010,
                  B10010101,
                  B10010001,
                  B10010001,
                  B10010101,
                  B01000010,
                  B00111100
                 };
char smile03[] = {8, 8,
                  B00111100,
                  B01000010,
                  B10100101,
                  B10010001,
                  B10010001,
                  B10100101,
                  B01000010,
                  B00111100
                 };

char derecha[] = {8, 8,
                  B00011000,
                  B00111100,
                  B01111110,
                  B11111111,
                  B00011000,
                  B00011000,
                  B00011000,
                  B00011000
                 };
char izquierda[] = {8, 8,
                  B00011000,
                  B00011000,
                  B00011000,
                  B00011000,
                  B11111111,
                  B01111110,
                  B00111100,
                  B00011000
                 };
                 
                 
void setup() {
  m1.init(); // MAX7219 initialization
  m1.setIntensity(2); // initial led matrix intensity, 0-15
    pinMode(2, INPUT);
  digitalWrite(2, HIGH);
      pinMode(13, INPUT);
  digitalWrite(13, LOW);
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}
void loop() {
/*  // Seting the LEDs On or Off at x,y or row,column position
  m1.setDot(6,2,true); 
  delay(1000);
  m1.setDot(6,3,true);
  delay(1000);
  m1.clear(); // Clears the display
  for (int i=0; i<8; i++){
    m1.setDot(i,i,true);
    delay(300);
  }
  m1.clear();
  // Displaying the character at x,y (upper left corner of the character)  
  m1.writeSprite(2, 0, A);
  delay(1000);
  m1.writeSprite(2, 0, B);
  delay(1000);
  m1.writeSprite(0, 0, smile01);
  delay(1000);
  
  m1.writeSprite(0, 0, smile02);
  delay(1000);
  
  m1.writeSprite(0, 0, smile03);
  delay(1000);
  
  for (int i=0; i<8; i++){
    m1.shiftLeft(false,false);
    delay(300);
  }
  m1.clear();*/
  // Arduino pin numbers

int x = analogRead(X_pin);

if (x > 600){  m1.writeSprite(0, 0, derecha);servo=servo-10;if(servo < 0){servo = 0;} myservo.write(servo);}
if (x < 400){  m1.writeSprite(0, 0, izquierda);servo=servo+10;if(servo > 180){servo = 180;} myservo.write(servo);}
if(x == 511){ m1.clear();}
  Serial.print("Switch:  ");
  Serial.print(digitalRead(SW_pin));
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(x);
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("test: ");
  Serial.println(digitalRead(13));
    Serial.print("Analog test: ");
  Serial.println(analogRead(2));
  Serial.print("\n\n");

}
