/* RUNAS_04
 * 
 * MEGA,RFID SERIAL Y RELE
 * 
 */

 
//EDITABLE
#define SPRINT      true
#define NEED_REPOSO false
#define RELE1    22
#define RELE2    23
#define DS       10

/*const int N_INPUTS = 1;
const int INPUTS[N_INPUTS] = {SVENT};
const int INPUTS_ISTATE[N_INPUTS] = {1};*/
const int N_OUTPUTS = 2;
const int OUTPUTS[N_OUTPUTS] = {RELE1,RELE2};
const int OUTPUTS_ISTATE[N_OUTPUTS] = {1,1};

const int SENSORES = 2;

char RESPUESTA0[]={'0','0','0','0','0','0','0','0','0','0','0','0','0','0'};

char RESPUESTA1[]={'0','0','0','0','0','0','0','0','0','0','0','0','0','0'};

char tag0[14];

char tag1[14];

boolean actual[] = {false,false};

char tagNumber[14];
String tagString;

//NO EDITABLE
boolean reposo = false;
boolean activo = false;
boolean resuelto = false;
unsigned long timer_print = 0;
////////////////////////////////////SETUP///////////////////////////////
//NO EDITABLE
void setup() {
  if(SPRINT){Serial.begin(9600);} 
//declara entradas
/*  for(int a = 0;a < N_INPUTS;a++){ 
    pinMode(INPUTS[a] , INPUT);
    digitalWrite(INPUTS[a] , INPUTS_ISTATE[a]);
  }*/
//declara salidas
  for(int a = 0;a < N_OUTPUTS;a++){ 
    pinMode(OUTPUTS[a] , OUTPUT);
    digitalWrite(OUTPUTS[a] , OUTPUTS_ISTATE[a]);
  }
//si necesita reposo
  if(NEED_REPOSO){reposo=true;activo=false;resuelto=false;}else{reposo=false;activo=true;resuelto=false;}
//EDITABLE

  Serial1.begin(9600); // the RDM6300 runs at 9600bps
  Serial2.begin(9600); // the RDM6300 runs at 9600bps
 

}

///////////////////////////////////////LOOP//////////////////////////////////////////
void loop() {
  if_reposo();
  if_activo();
  if_resuelto();
  showme();
}

////////////////////////////////////////FUNCIONES///////////////////////////////////
//EDITABLE
void if_reposo()
{
  if(reposo){

  }
}

void if_activo()
{
  if(activo){

    int resu = 0;

    for(int a = 0;a < SENSORES;a++){

      switch(a){

        case 0:{
        
          if(lee_rdm630(a)){if(tag0 == RESPUESTA0){actual[a] = true;}else{actual[a] = false;}if(SPRINT){Serial.println("leo0");}}
    
          if(actual[a] == true){resu++;}

  
         break;}
  
        case 1:{
        
          if(lee_rdm630(a)){if(tag1 == RESPUESTA1){actual[a] = true;}else{actual[a] = false;}if(SPRINT){Serial.println("leo1");}}
    
          if(actual[a] == true){resu++;}

  
         break;}
  
        }
        
      }

    if(resu==SENSORES){    digitalWrite(RELE2,LOW);
                            digitalWrite(RELE1,LOW);}else{resu = 0;}
    
    }

}

void if_resuelto()
{
  if(resuelto){
    digitalWrite(RELE2,LOW);
    digitalWrite(RELE1,LOW);
  }
}


boolean lee_rdm630 (int cual)
{
  boolean receivedTag = false;
  switch (cual){


    case 0:
    {
      while (Serial1.available()){
        unsigned long  BytesRead = Serial1.readBytesUntil(3, tag0, 15);//EOT (3) is the last character in tag
        tag0[0] = '0';
        receivedTag=true;  
    } 

    break;}

    case 1:
    {
      while (Serial2.available()){
        unsigned long  BytesRead = Serial2.readBytesUntil(3, tag1, 15);//EOT (3) is the last character in tag
        tag1[0] = '0';
        receivedTag=true;
    }
      
    break;}

    
    }

    
  return receivedTag;   
}

void showme ()
{
  if(SPRINT && millis() - timer_print > 1000)
  {
    Serial.println("------NUEVA MEDICION------");
      Serial.print("TAG ");
      Serial.print('0');
      Serial.print(" :");
      tagString = tag0;
      Serial.println(tagString);
      Serial.print("TAG ");
      Serial.print('1');
      Serial.print(" :");
      tagString = tag1;
      Serial.println(tagString);
    timer_print = millis();
  }
}

//NO EDITABLE
//comprueba el estado de un sensor
boolean check (boolean cual, int entrada, int ds)
{
  boolean resu = false;
  int contador = 0;  
  if(cual){ while(digitalRead(entrada) == 1 && resu == false){delay(ds);contador++;if(contador == 5){resu = true;}}
  }else{    while(digitalRead(entrada) == 0 && resu == false){delay(ds);contador++;if(contador == 5){resu = true;}}}  
  return resu; 
}
