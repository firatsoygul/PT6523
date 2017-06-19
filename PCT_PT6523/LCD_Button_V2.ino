#include <SPI.h>

const int slaveSelectPin = 10;
int ADR = 130;
int n=0;
byte Letter1[16]={28,19,28,112,24,32,24,32,24,99,0,0,0,0,0,0};  // HELLO
byte Letter2[16]={25,7,24,99,28,85,24,32,0,227,0,0,0,0,0,0};  // WORLD

const int buttonPin = 2; 

int lastButtonState;

void setup() {

  pinMode(slaveSelectPin, OUTPUT);
  SPISettings(30000, MSBFIRST, SPI_MODE0);
  SPI.begin();

  pinMode(buttonPin, INPUT);

  CLS();

}

void loop() {

  lastButtonState=digitalRead(buttonPin);

      
  while(lastButtonState==digitalRead(buttonPin)){
      
        delay(10);
                
    }

byte Out[16];
byte j=1;

for(int i=0; i<= 14; i+=2){

  Out[i]=(Letter1[i] << j) | (Letter1[i+1] >> (8-j));
  if(i<2){
    Out[i+1]=Letter1[i+1] << j;}
  else if(i>=14){
    Out[i]=Letter1[i+1];
    Out[i+1]=0;}
  else{
    Out[i+1]=(Letter1[i+1] << j) | (Letter1[i+2] >> (7-j));  
  }

j++;

}

digitalWrite(slaveSelectPin, LOW);
SPI.transfer(ADR);
digitalWrite(slaveSelectPin, HIGH);
SPI.transfer(0); 

for(int i=0; i<=14; i++){
  SPI.transfer(Out[i]);
}

SPI.transfer(0);
SPI.transfer(0);
SPI.transfer(0);
SPI.transfer(0);

SPI.transfer(0); 
digitalWrite(slaveSelectPin, LOW); //EOT 


  lastButtonState=digitalRead(buttonPin);

   while(lastButtonState==digitalRead(buttonPin)){
      
        delay(10);
        n++;

        if(n>=300){
          n=0;
          CLS(); 
          goto End;
        }
                
    }

n=0;
j=1;

for(int i=0; i<= 14; i+=2){

  Out[i]=(Letter2[i] << j) | (Letter2[i+1] >> (8-j));
  if(i<2){
    Out[i+1]=Letter2[i+1] << j;}
  else if(i>=14){
    Out[i]=Letter2[i+1];
    Out[i+1]=0;}
  else{
    Out[i+1]=(Letter2[i+1] << j) | (Letter2[i+2] >> (7-j));  
  }

j++;

}

digitalWrite(slaveSelectPin, LOW);
SPI.transfer(ADR);
digitalWrite(slaveSelectPin, HIGH);
SPI.transfer(0);

for(int i=0; i<=14; i++){
  SPI.transfer(Out[i]);
}

SPI.transfer(0);
SPI.transfer(0);
SPI.transfer(0);
SPI.transfer(0);

SPI.transfer(0); 
digitalWrite(slaveSelectPin, LOW); //EOT 


  lastButtonState=digitalRead(buttonPin);

   while(lastButtonState==digitalRead(buttonPin)){
      
        delay(10);
        n++;

        if(n>=300){
          n=0;
          CLS();        
        }
                
    }

End:
n=0;
delay(10);
}

void CLS(){ 

      digitalWrite(slaveSelectPin, LOW);
      SPI.transfer(ADR);
      digitalWrite(slaveSelectPin, HIGH);

       for (int k=0; k<=19; k++){

         SPI.transfer(B00000000);    
         delay(10);
        
       }        
       
      SPI.transfer(0);
      digitalWrite(slaveSelectPin, LOW);  

      return;

}

