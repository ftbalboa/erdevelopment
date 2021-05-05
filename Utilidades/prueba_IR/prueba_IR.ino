
#include <IRremote.h>
int RECV_PIN = 5; 

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Empezamos la recepción  por IR
}


void loop() {
  //P CONTROL CAR
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    if(results.value == 553536955){Serial.println("play");};
    if(results.value == 3855596927){Serial.println("EQ");};
    if(results.value == 2747854299){Serial.println("vol+");};
    if(results.value == 4034314555){Serial.println("vol-");};
    if(results.value == 3810010651){Serial.println("CH-");};
    if(results.value == 5316027){Serial.println("CH");};
    if(results.value == 4001918335){Serial.println("CH+");};
    if(results.value == 2534850111){Serial.println("1");};
    if(results.value == 1033561079){Serial.println("2");};
    if(results.value == 1635910171){Serial.println("3");};
    if(results.value == 2351064443){Serial.println("4");};
    if(results.value == 1217346747){Serial.println("5");};
    if(results.value == 71952287){Serial.println("6");};
    if(results.value == 851901943){Serial.println("7");};
    if(results.value == 465573243){Serial.println("8");};
    if(results.value == 1053031451){Serial.println("9");};
    if(results.value == 3238126971 || results.value == 16738455){Serial.println("0");};
    irrecv.resume(); // empezamos una nueva recepción
  }

}


//P/CONTROL KEISA
/*  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    if(results.value == 16736925){Serial.println("arriba");};
    if(results.value == 16720605){Serial.println("izquierda");};
    if(results.value == 16761405){Serial.println("derecha");};
    if(results.value == 16754775){Serial.println("abajo");};
    if(results.value == 16712445){Serial.println("OK");};
    if(results.value == 16738455){Serial.println("1");};
    if(results.value == 16750695){Serial.println("2");};
    if(results.value == 16756815){Serial.println("3");};
    if(results.value == 16734885){Serial.println("9");};
    if(results.value == 16724175){Serial.println("4");};
    if(results.value == 16718055){Serial.println("5");};
    if(results.value == 16743045){Serial.println("6");};
    if(results.value == 16716015){Serial.println("7");};
    if(results.value == 16726215){Serial.println("8");};
    if(results.value == 16730805){Serial.println("0");};
    if(results.value == 16728765){Serial.println("asterisco");};
    if(results.value == 16732845){Serial.println("numeral");};
    irrecv.resume(); // empezamos una nueva recepción
      

  }*/
