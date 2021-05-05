#include <Ethernet.h>
#include <SPI.h>


byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x02 };
byte ip[] = { 192, 168, 1, 001 };
byte server[] = { 00, 000, 000, 00 }; // Google
unsigned long contador = 0;

EthernetClient client;

void setup()
{
  Serial.begin(9600);
Serial.println("Iniciando");
 if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for (;;)
      ;
  }
  // print your local IP address:
  printIPAddress();


  
 /* if (client.connect("192.168.1.101", 23)) {
    Serial.println("connected");
  } else {
    Serial.println("connection failed");
  }*/
}

void loop()
{
  if ((millis() - contador) >= 5000) { // Esto lo puedes dejar como estaba, pero creo que es más ilustrativo así
    contador = millis();
    if (client.connect("192.168.1.101", 23)) {
    Serial.println("me conecte");
  }else{Serial.println("no me conecte");}
    char c = client.read();
    if(c != -1){
      Serial.println(c);
     // client.write("2");
    }
    client.stop();
  }
}


void printIPAddress()
{
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }

  Serial.println();
}
