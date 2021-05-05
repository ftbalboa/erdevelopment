#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>


// Direccion MAC
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xE7 };

// IP del servidor
IPAddress mqtt_server(192, 168, 0, 100);

// Topic con el que trabajamos
const char* topicName = "main";

EthernetClient ethClient;
PubSubClient client(ethClient);

void setup()
{
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
  }
  client.setServer(mqtt_server, 1883);
}

void loop()
{
  if (!client.connected()) {
    Serial.print("Connecting ...\n");
    client.connect("Arduino Client");
  }
  else {
    // Envio

    client.publish(topicName, "Hey RPI");
  }
  // Tiempo entre envios (en ms)
  delay(5000);
}
