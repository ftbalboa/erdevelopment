     int speakerPin = 4;
  
     int numTones = 10;
    // int tones[ ] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440,466, 494};
                       // mid C C# D D# E F F# G G# A

     void setup()
        { }

     void loop()
        {
             for (int i = 0; i < numTones; i++)
                 {
                     tone(speakerPin, 1000);
                     delay(100);
                     noTone(speakerPin);
                     delay(900);
                 }
                 
             noTone(speakerPin);
       }
