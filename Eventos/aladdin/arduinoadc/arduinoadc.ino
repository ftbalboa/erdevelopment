int MUESTRA = 1000;

int LIMITE  = 70;

int promedio_viejo = 0;

void setup() {
  pinMode(A0 , INPUT);
  pinMode(2,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  digitalWrite(2, HIGH);
  Serial.begin(9600);
}

void loop() {
digitalWrite(12,LOW);
digitalWrite(13,LOW);
int promedio_actual = promedio();
Serial.print(promedio_actual);Serial.print(" Diferencia: ");Serial.println(promedio_viejo-promedio_actual);
if((promedio_viejo - promedio_actual > LIMITE) ||( promedio_viejo - promedio_actual < -LIMITE)){digitalWrite(12,HIGH);digitalWrite(13,HIGH);Serial.println("TOCANDO");delay(1000);};
promedio_viejo = promedio_actual;
}

void laser ()
{
 // if(analogRead(A0) < 200){digitalWrite(2 , LOW);} else {digitalWrite(2 , HIGH);}
}

int promedio ()
{
  unsigned long total = 0;
  for(int i=0;i<MUESTRA;i++){
    total = total + analogRead(A0);
    }
  total = total / MUESTRA;
    return total;
  }
