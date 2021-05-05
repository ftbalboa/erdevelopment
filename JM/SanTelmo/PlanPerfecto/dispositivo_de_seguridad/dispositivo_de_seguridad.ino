void setup() {
  pinMode(14 , INPUT);
  digitalWrite(14 , HIGH);
  pinMode(15 , OUTPUT);
  digitalWrite(15 , LOW);
    pinMode(16 , INPUT);
  digitalWrite(16 , HIGH);
}

void loop() {
if(digitalRead(16)==LOW){delay(100);if(digitalRead(16)==LOW){
  if(digitalRead(14)==LOW){delay(100);if(digitalRead(14)==LOW){delay(5000);digitalWrite(15 , HIGH); delay(5000);} }
  else{digitalWrite(15 , LOW);}}}

}
