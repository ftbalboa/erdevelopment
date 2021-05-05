unsigned long mostrar = 0;
unsigned long timer = 0;

void setup() {
  Serial.begin(9600);
  delay(5000);
  Serial.println("INICIE");
}

void loop() { 

 
   while (Serial.available()>0) 
   {
        char option = Serial.read();
        Serial.println(option);
   }

  if(millis() > timer + 1000){timer = millis();Serial.println("A");}
   
}
