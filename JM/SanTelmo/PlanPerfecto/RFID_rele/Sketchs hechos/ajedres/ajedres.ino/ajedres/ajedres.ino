const int libros = 13;
const int rel = 10;

void setup() {
 pinMode(rel,OUTPUT);
 pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);
 pinMode(libros,INPUT);
 digitalWrite(libros,HIGH);
 
Serial.begin(9600);

}

void loop() {

  Serial.print(digitalRead(libros));


  
  if(digitalRead(libros)){
       digitalWrite(rel,HIGH);
       
    }else{
      
      digitalWrite(rel,LOW);
      }

}
