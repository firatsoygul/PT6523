#include <SPI.h>

const int slaveSelectPin = 10;

byte k=0;
byte ADR = 130;
byte Letter[24]={28,19,28,112,24,32,24,32,24,99,0,0,25,7,24,99,28,85,24,32,0,227,0,0};
int n=0;

void setup() {

Serial.begin(9600);

pinMode(slaveSelectPin, OUTPUT);

SPISettings(38000, MSBFIRST, SPI_MODE0);
SPI.begin();

}

void loop() {

byte Out[16];
byte j=1;

n=k;

for(int i=0; i<= 14; i+=2){

  Out[i]=(Letter[n] << j) | (Letter[n+1] >> (8-j));
  if(i<2){
    Out[i+1]=Letter[n+1] << j;}
  else if(i>=14){
    Out[i]=Letter[n+1];
    Out[i+1]=0;}
  else{
    Out[i+1]=(Letter[n+1] << j) | (Letter[n+2] >> (7-j));  
  }

  if((n+2)>22){
    n=0;
    Out[i+1]=Letter[23]<<j|Letter[0]>>(7-j);}
  else{
    n+=2;
  }

j++;

}

if((k+2)>22){
    k=0;}
else{
    k+=2;
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

delay(500);

}
