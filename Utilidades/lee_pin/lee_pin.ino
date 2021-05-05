int lectura=0;

void setup() {
  pinMode(2 , INPUT);
  digitalWrite(2, HIGH);
  Serial.begin(9600);

}

void loop() {
  Serial.print("Lectura ");
  Serial.print(lectura);
  Serial.print(": ");
  Serial.println(digitalRead(2));
  delay(1000);
  lectura++;
}
