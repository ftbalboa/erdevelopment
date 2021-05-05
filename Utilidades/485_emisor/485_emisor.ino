void setup() 
{ 
  delay(1000);
  Serial.begin(9600);
  Serial1.begin(9600);
} 
 
void loop() 
{ 
  Serial1.println('5');
  Serial1.println('2');
  Serial.println("52");
  delay(250);                           
} 
