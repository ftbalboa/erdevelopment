

#define RxPin1 19 //Pin to read data
#define TxPin1 18 //Pin to write data

#define RxPin2 17 //Pin to read data
#define TxPin2 16 //Pin to write data

#define RxPin3 15 //Pin to read data
#define TxPin3 14 //Pin to write data



String tagString;
char tagNumber[14];
boolean receivedTag;

void setup() {
  Serial.begin(9600);

  //while (!Serial1) ;
  Serial1.begin(9600); // the RDM6300 runs at 9600bps
  Serial.println("RFID1 Reader...ready!");
  Serial2.begin(9600); // the RDM6300 runs at 9600bps
  Serial.println("RFID2 Reader...ready!");
  Serial3.begin(9600); // the RDM6300 runs at 9600bps  
  Serial.println("RFID3 Reader...ready!");
}

void loop() {
  receivedTag=false;
  while (Serial1.available()){
    Serial.println("rfid 1 available");
    int BytesRead = Serial1.readBytesUntil(3, tagNumber, 15);//EOT (3) is the last character in tag
    tagNumber[0] = '0';
    Serial.println(BytesRead);
    receivedTag=true;
  }  

  while (Serial2.available()){
    Serial.println("rfid 2 available");
    int BytesRead = Serial2.readBytesUntil(3, tagNumber, 15);//EOT (3) is the last character in tag
    tagNumber[0] = '0';
    Serial.println(BytesRead);
    receivedTag=true;
  }  

  while (Serial3.available()){
    Serial.println("rfid 3 available");
    unsigned long BytesRead = Serial3.readBytesUntil(3, tagNumber, 15);//EOT (3) is the last character in tag
    tagNumber[0] = '0';
    Serial.println(BytesRead);
    receivedTag=true;
  }  

  if (receivedTag){
    tagString=tagNumber;
    Serial.println();
    Serial.print("Tag Number: ");
    Serial.println(tagString);

    memset(tagNumber,0,sizeof(tagNumber)); //erase tagNumber
  }  
}


