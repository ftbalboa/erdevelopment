//PINMODES

int rele = 9;

int canonin = 7;

void setup() {

  pinMode(rele , OUTPUT);
  digitalWrite(rele , HIGH);
  pinMode(canonin , INPUT);
  digitalWrite(canonin , HIGH);
  Serial.begin(9600);

}

void loop() {

  if(digitalRead(canonin) == false){

    delay(500);
    
    digitalWrite(rele , LOW);
    
    delay(500);
    
    }

  if(digitalRead(canonin) == true){
    
    digitalWrite(rele , HIGH);
    
    
    }
    Serial.println(digitalRead(canonin));

}
