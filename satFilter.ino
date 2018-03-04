#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
String protocol ="";
String coma = "";
String enCom = "";
bool proto = false;
int a = 0;
int b = 0;
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}
void loop() { // run over and over
 if (mySerial.available()) {
  char inByte = mySerial.read();
  if(inByte == '$' or inByte == 'G' or inByte == 'P' or inByte == 'G' or inByte == 'G' or inByte == 'A'){
   protocol+=inByte;
  }
///Protocolo
  if(protocol == "$GPGGA"){
   Serial.print("$GPGGA Latitud: ");
   protocol ="";
   proto = true;
  }  
//getLatitud
  if(proto == true){
   if(inByte ==','){
    coma+=inByte;
   }
   if(coma == ",,"){
    if(inByte !=','){
     if(inByte !='.'){
      Serial.write(inByte);
      a++;
      if(a==2){
       Serial.print(".");
      }
     }
    }
   }
  }
//getLongitud
if(proto == true){
  if(enCom == "N,"){
    if(inByte == ','){
      enCom ="";
      }
    if(enCom == "N,"){
     if(inByte !='.'){
      if(b>0){
        Serial.write(inByte);
      }
      if(b==0 and inByte == '0'){
          Serial.print("-");
      }  
      b++;
      if(b==3){
       Serial.print(".");
      }
     }
    }
   }
  if(inByte == 'N'){
    enCom+= inByte;
    Serial.print(" Longitud:");
   }
   if(inByte == ',' and enCom == "N"){
    enCom+= inByte;
    Serial.print(" ");
   }
  }
  //NL & CR
  if(inByte == '*'){
    a=0;
    b=0;
    protocol="";
    coma = "";
    enCom = "";
    if(proto == true){
      proto = false;
      Serial.println();
    }
   }
  }
}
