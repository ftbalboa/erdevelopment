#include <rdm630.h>



#include <SoftwareSerial.h>

rdm630 rfid(3, 0);  //TX-pin of RDM630 connected to Arduino pin 6
rdm630 rfid2(44, 0);

void setup()
{
    delay(1000);
    Serial.begin(9600);  // start serial to PC
//    rfid.begin();
    rfid2.begin();
    Serial.println("Start");
}

void loop()
{
//unsigned int resu1=lee_rdm630(rfid);
unsigned int resu2=lee_rdm630(rfid2);
//if(resu1 != 0){Serial.println(resu1);}
if(resu2 != 0){Serial.println(resu2);}
    
}

unsigned int lee_rdm630 (rdm630 &lector)
{

    byte data[6];
    byte length;
    unsigned long result = 0;
    if(lector.available()){
        lector.getData(data,length);
        //concatenate the bytes in the data array to one long which can be 
        //rendered as a decimal number
          result = 
          ((unsigned long int)data[1]<<24) + 
          ((unsigned long int)data[2]<<16) + 
          ((unsigned long int)data[3]<<8) + 
          data[4];              
    }
    return result;
}
