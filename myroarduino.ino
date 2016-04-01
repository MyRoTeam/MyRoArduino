#include <SoftwareSerial.h>

SoftwareSerial mySerial(0,1);//RX,TX
int counter = 0;
int state = 0;
int pin = 0;
int speedVal = 0;

void setup() {
  
  Serial.begin(115200);

  pinMode(6 ,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(9,OUTPUT);
  
  //wait for serial to connect
  while(!Serial){
    ;
  }

  //mySerial referes to Serial of BLE Module
  mySerial.begin(115200);

  //Arduino<--->BLE<--->Phone
  

}

void loop() {

  
  //check if there is data that phone sent to arduino
  if(mySerial.available()){
    byte b = mySerial.read();
    Serial.print("TEST: ");
    Serial.println((int)b);
    if(b == 72 || b == 76){
      Serial.println("got a valid state");
      state = b;
      if(counter != 1)counter++;
      Serial.print("counter: ");
      Serial.print(counter);
    }
    else if(counter == 1 && ((int)b == 13 || (int)b == 11 || (int)b == 9)){
          pin = (int)b;
          counter++;      
    }
    else if(counter == 2){
          speedVal = (int)b;
          speedVal = (abs(speedVal - 255) + 10) * 10;
          counter = 0;
    }
   
  }

  
   if(state == 72 && speedVal != 0 && pin != 0){
      Serial.println("got high");
      digitalWrite(pin,HIGH);
      delay(speedVal);
      digitalWrite(pin,LOW);
      delay(speedVal);
    }
    else if(state == 76 && pin != 0){
      Serial.println("got low");
      digitalWrite(pin,LOW);
    }
 
  
  
  

}

