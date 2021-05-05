#include <SPI.h>
#include <Ethernet.h>

// network configuration.  gateway and subnet are optional.

 // the media access control (ethernet hardware) address for the shield:
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };  
IPAddress ip(192, 168, 0, 101);
IPAddress myDns(192,168,0, 1);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 0, 0);
unsigned long contador = 0;
// telnet defaults to port 23
EthernetServer server = EthernetServer(23);

void setup()
{
  pinMode(2,INPUT);
  digitalWrite(2,HIGH);
      Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // initialize the Ethernet device not using DHCP:
    Ethernet.begin(mac, ip, myDns, gateway, subnet);
  }



  // start listening for clients
  server.begin();
  Serial.println("Todo ok");
}

void loop()
{
  // if an incoming client connects, there will be bytes available to read:
/*  EthernetClient client = server.available();
  if (client == true) {*/
    // read bytes from the incoming client and write them back
    // to any clients connected to the server:
    if ((millis() - contador) >= 500) { // Esto lo puedes dejar como estaba, pero creo que es más ilustrativo así
    contador = millis(); // Aquí estabas perdiendo potencialmente millis, ya que cuando reasignas millis a contador, puede haber pasado alguno más de 1000
      if(digitalRead(2)==0){    server.write('R');}
  else{
    int a = 3;
    server.write('3');
      EthernetClient client = server.available();
  if (client) {
    // read bytes from the incoming client and write them back
    // to any clients connected to the server:
    char c = client.read();
    Serial.println(c);
  }}
    }
    

}
