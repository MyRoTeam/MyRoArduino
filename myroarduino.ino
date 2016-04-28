#include <SoftwareSerial.h>

SoftwareSerial mySerial(0,1);//RX,TX
int state = 0;
char dir = 'X';
int spd = 0;


#define LEFT 5
#define RIGHT 9

void setup() {
  
  Serial.begin(9600);

  pinMode(LEFT ,OUTPUT);
  pinMode(RIGHT,OUTPUT);

  
  //wait for serial to connect
  while(!Serial){
    ;
  }

  //mySerial referes to Serial of BLE Module
  mySerial.begin(9600);

  //Arduino<--->BLE<--->Phone


 
}

void loop() {

  
  //check if there is data that phone sent to arduino
  if(mySerial.available()){
    byte b = mySerial.read();

    //X = 88
    
    if(b == 88){
      if(state == 0 || state ==2){
        state = 1;
      }
     
      
    }
    else if(b == 89){

        if(state = 1){

            state = 2;
          
        }
    
       
    }
    else{

      if(state == 1){

          Serial.println("This is a direction value");
          if(b == 70) dir = 'F';
          else if(b == 76) dir = 'L';
          else if(b == 82) dir = 'R';
          else if(b == 66) dir = 'B';

      }
      else if(state == 2){

          Serial.println("This is a speed value");
          spd = b;

          if(dir == 'F') {
            analogWrite(LEFT,spd);
            analogWrite(RIGHT,spd);
          }
          else if(dir == 'L'){
            analogWrite(LEFT,spd);
            analogWrite(RIGHT,0);
          }
          else if(dir == 'R'){
            analogWrite(LEFT,0);
            analogWrite(RIGHT,spd);
          }
          else{
            analogWrite(LEFT,0);
            analogWrite(RIGHT,0);
          }

          state = 0;

      }


    }
    }

   
  }

  
   
  
  
  



