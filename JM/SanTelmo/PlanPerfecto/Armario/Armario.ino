//PINMODES

int rele = 13;

int canonin = 2;

void setup() {

  pinMode(rele , OUTPUT);
  digitalWrite(rele , HIGH);
  pinMode(canonin , INPUT);
  digitalWrite(canonin , HIGH);
  Serial.begin(9600);

}

void loop() {

  if(digitalRead(canonin) == false){

    delay(11000);
    
    digitalWrite(rele , LOW);
    
    delay(2000);
    
    }

  if(digitalRead(canonin) == true){
    
    digitalWrite(rele , HIGH);
    
    
    }
    Serial.println(digitalRead(canonin));

}
