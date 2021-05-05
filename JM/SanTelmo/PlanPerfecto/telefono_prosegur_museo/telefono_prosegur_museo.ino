    //INCLUDES
    #include <Keypad.h>            // Prog_19_1
    #include "Arduino.h"
    #include "SoftwareSerial.h"
    #include "DFRobotDFPlayerMini.h"
    
    //GLOBALES

    //DECLARACIONES LIB.MP3

    /******AUDIOS******
    1-SUENA EL TELEFONO
    2-HABLA PROSEGUR
    3-CLAVE INCORRECTA
    4-CLAVE CORRECTA
    5-TONO DE TECLA
    6-REPITE PROSEGUR
    7-REPITE PROSEGUR
    ******************/

     SoftwareSerial mySoftwareSerial(16, 3); // RX, TX
     DFRobotDFPlayerMini myDFPlayer;
     void printDetail(uint8_t type, int value);

    //DECLARACIONES LIB KEYPAD
      
     const byte Filas = 4;          //Cuatro filas
     const byte Cols = 3;           //Cuatro columnas

     byte Pins_Filas[] = {6, 7, 8, 9};     //Pines Arduino para las filas
     byte Pins_Cols[] = { 10, 4, 5};     // Pines Arduinopara las columnas
     char Teclas [ Filas ][ Cols ] =
          {
              {'1','2','3'},
              {'4','5','6'},
              {'7','8','9'},
              {'*','0','#'}
          };
          
     Keypad Teclado1 = Keypad(makeKeymap(Teclas), Pins_Filas, Pins_Cols, Filas, Cols);

    //VAR
    int reset = 13; 
     int puerta = 2;
     int tubo = 11;
     boolean puerta_flag = 0;
     char clave[] = {'7','4','1','9' ,'7' ,'5','0','8'};
    // byte clave_ingresada[4];
     boolean correcta = 0;
     int posicion = 0;
     int bien = 0;
     int led = 14;
     int tx = 12;
     unsigned int prevmilis = 0;
     int intervalo = 500; //INTERVALO DE PARPADEO DEL LED 
     boolean led_flag = 0;
     boolean puerta_flag2 = false;
     boolean txflag = false;
     int lope = 0;
     int recuerdo = 0;
     boolean rec = false;
     
    //SETUP
     void setup()
        {  
          

          delay(10000);
          
            mySoftwareSerial.begin(9600);
           pinMode(puerta, INPUT);
            pinMode(tubo, INPUT);
            digitalWrite(tubo , HIGH);
            pinMode(reset, OUTPUT);
            digitalWrite(reset , HIGH);
            pinMode(led, OUTPUT);
            pinMode(tx, OUTPUT);
            digitalWrite(led, LOW);
            digitalWrite(tx, LOW);
            Serial.begin(9600);

            if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
              Serial.println(F("Unable to begin:"));
              Serial.println(F("1.Please recheck the connection!"));
              Serial.println(F("2.Please insert the SD card!"));
              digitalWrite(reset , LOW);
              delay(100);
              digitalWrite(reset , HIGH);
              while(true);
  }
  
            Serial.println(F("DFPlayer Mini online."));
  
            myDFPlayer.volume(30);  //Set volume value. From 0 to 30
            //myDFPlayer.play(1);  //Play the first mp3
      //      attachInterrupt(0, puertaAbierta, FALLING) ;
        }


    //LOOP
     void loop()
        {       
          
          if(digitalRead(puerta)==false && puerta_flag == false && puerta_flag2 == false){
            
            delay(500);
            
            if(digitalRead(puerta)==false){puerta_flag = true;puerta_flag2 = true;}
            
            
            
            }
          
          if(digitalRead(puerta)==true &&  puerta_flag2 == true){
            
            delay(500);
            
            if(digitalRead(puerta)==true){digitalWrite(reset , HIGH);puerta_flag = false;puerta_flag2 = false;txflag = false;digitalWrite(tx , 0);}
            
            
            
            }
            
            if(puerta_flag/*digitalRead(puerta)==1*/){
        //          Serial.println("puerta");

                  delay(3000);
        
                  myDFPlayer.loop(1);

                  digitalWrite(led, LOW);
                  
                  led_flag = 1;
                  
                  while(digitalRead(tubo)==0){
//Serial.println(digitalRead(tubo));
                    if((millis() - prevmilis) > intervalo){
                      
                      prevmilis = millis();
                      
                      if(led_flag){ digitalWrite(led, LOW); led_flag = 0;}
                      
                      else{ digitalWrite(led, HIGH); led_flag = 1;}
                      
                      }
                    
                    }
                
          //      Serial.println("tubo");
                
                digitalWrite(led, HIGH);
                
                led_flag = 0;

                myDFPlayer.play(2);

                delay(13000);


                while(correcta == 0){

                    delay(10);
                    lope++;
                    if(lope > 500){
                    
                    }
                   
                    
                   char pulsacion = Teclado1.getKey() ;
                   
                      if (pulsacion != 0) {             // Si el valor es 0 es que no se
                          Serial.println(pulsacion);   // se ha pulsado ninguna tecla*/
                //           Serial.println(clave[posicion]); 
                //          Serial.print("posicion");
                //        Serial.print(posicion);
                          char hey = clave[posicion];

                          recuerdo = 0;
                          
                          myDFPlayer.play(5);

                          
                          
                          if (pulsacion == hey){
                  //        Serial.print("esa");
                            bien++;
                            
                            }  else {
 
                              bien = 0;
                              
                              }

                          if (posicion == 7){

                              delay(400);
                            
              //              Serial.print("bien");
            //                Serial.print(bien);
                            if(bien == 8){

                              myDFPlayer.play(4);
                              
                              posicion = 0;

                              bien = 0;

                              correcta = 1;

                              digitalWrite(reset , LOW);
                              
                              } else {

                                myDFPlayer.play(3);

                                delay(2000);
                                
                                posicion = 0;

                                bien = 0;
                                
                                }
                            
                            
                            } else {
                              posicion++;}
                      
                        
                      }

               if(recuerdo == 6000){

                recuerdo = 0;

                if(rec){myDFPlayer.play(6);delay(5000);rec = false;}else{myDFPlayer.play(7);delay(5000);rec = true;}

                
                
                }
                delay(10);
                recuerdo++;
                
                }

                digitalWrite(tx , HIGH);
                digitalWrite(led, LOW);

                correcta = 0;


                puerta_flag=false;

                txflag = true;
                   
                  }


          
          
  /*              char pulsacion = Teclado1.getKey() ;
                if (pulsacion != 0)              // Si el valor es 0 es que no se
                    Serial.println(pulsacion);   // se ha pulsado ninguna tecla*/
        }


    //Interrupts

 /*    void puertaAbierta(){
      
      
      puerta_flag = 1;
      
//      Serial.println("IN");
      
      
      }*/
