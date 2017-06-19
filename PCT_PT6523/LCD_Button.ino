#include <SPI.h>

const int slaveSelectPin = 10;
int ADR = 130;
int j=0;
int n=20;
int M[8]={128,64,32,16,8,4,2,1};

const int buttonPin1 = 2;

int buttonState1; 
int lastButtonState1;

void setup() {

  pinMode(slaveSelectPin, OUTPUT);
  SPISettings(30000, MSBFIRST, SPI_MODE0);
  SPI.begin();

  pinMode(buttonPin1, INPUT);

}

void loop() {

  lastButtonState1=digitalRead(buttonPin1);

      digitalWrite(slaveSelectPin, LOW);
      SPI.transfer(ADR);
      digitalWrite(slaveSelectPin, HIGH);

      if(n==20){

       for (int k=0; k=19; k++){

         SPI.transfer(255);
         delay(10);
         goto Lbl;
        
       }        
      }
      
      for (int k=0; k<n; k++){

        SPI.transfer(0);
        delay(10);
        
      }

      SPI.transfer(M[j]);
      delay(10);

      for (int k=0; k<(18-n); k++){

        SPI.transfer(0);
        delay(10);
        
      }      

 Lbl:
 
      SPI.transfer(1);
      digitalWrite(slaveSelectPin, LOW);


      
    while(lastButtonState1==digitalRead(buttonPin1)){
      
        delay(10);
                
    }

    n++;
    
    if(n>20){n=0;}

    else if(n<0){n=19;}
      
  //delay(10000);

}
