void setup() 
{ 
  delay(1000);
  Serial.begin(9600);
  Serial.println("Ready2");   
} 
 
void loop() 
{  
  while (Serial.available()) 
  {
    char recibido = Serial.read();
    if(recibido != 13 && recibido != 10){
    Serial.print(recibido); 
    }
    
  }
  Serial.println();
  delay(250);
} 
