#include <SPI.h>

const int slaveSelectPin = 10;

byte k=0;
byte ADR = 130;
//byte Letter[24]={28,19,28,112,24,32,24,32,24,99,0,0,25,7,24,99,28,85,24,32,0,227,0,0};
void karakter(char gk[]);
void yazdir();

byte Letter[30];
int n=0;
int kuz;

void setup() {

Serial.begin(9600);

pinMode(slaveSelectPin, OUTPUT);
// initialize SPI:
SPISettings(38000, MSBFIRST, SPI_MODE0);
SPI.begin();

Serial.begin(9600);

}

void loop() {
  for(int i=0; i<5; i++){
  karakter("* BURAYA YAZILAN METIN EKRANDA KAYDIRILACAK...");
  yazdir();
  }
  



 }

void yazdir() {

byte Out[17];
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
SPI.transfer(0); //First unused byte
for(int i=0; i<=14; i++){
  SPI.transfer(Out[i]);
}

SPI.transfer(0);
SPI.transfer(0);
SPI.transfer(0);
SPI.transfer(0);

SPI.transfer(0);
digitalWrite(slaveSelectPin, LOW); //EOT

delay(400);

}

void karakter(char gk[])
{
  kuz = 0;
  while( gk[kuz]!='\0' )
      kuz++;
   
   int d = -2;
   for (int j=0;j<=kuz+1;j++) {
    switch (gk[j]) {
      case ' ' : Letter[d+2] = 0; Letter[d+3] = 0; d+=2; break;
      case 'A' : Letter[d+2] = 28; Letter[d+3] = 83; d+=2; break;
      case 'B' : Letter[d+2] = 0; Letter[d+3] = 243; d+=2; break;
      case 'C' : Letter[d+2] = 24; Letter[d+3] = 96; d+=2; break;
      //case 'Ç' : Letter[d+2] = 21; Letter[d+3] = 80; d+=2; break;
      case 'D' : Letter[d+2] = 0; Letter[d+3] = 227; d+=2; break;
      case 'E' : Letter[d+2] = 28; Letter[d+3] = 112; d+=2; break;
      case 'F' : Letter[d+2] = 28; Letter[d+3] = 64; d+=2; break;
      case 'G' : Letter[d+2] = 24; Letter[d+3] = 114; d+=2; break;
      case 'H' : Letter[d+2] = 28; Letter[d+3] = 19; d+=2; break;
      case 'I' : Letter[d+2] = 0; Letter[d+3] = 224; d+=2; break;
      case 'J' : Letter[d+2] = 8; Letter[d+3] = 35; d+=2; break;
      case 'K' : Letter[d+2] = 28; Letter[d+3] = 12; d+=2; break;
      case 'L' : Letter[d+2] = 24; Letter[d+3] = 32; d+=2; break;
      case 'M' : Letter[d+2] = 26; Letter[d+3] = 11; d+=2; break;
      case 'N' : Letter[d+2] = 26; Letter[d+3] = 7; d+=2; break;
      case 'O' : Letter[d+2] = 24; Letter[d+3] = 99; d+=2; break;
      case 'Ö' : Letter[d+2] = 14; Letter[d+3] = 58; d+=2; break;
      case 'P' : Letter[d+2] = 28; Letter[d+3] = 81; d+=2; break;
      case 'R' : Letter[d+2] = 24; Letter[d+3] = 85; d+=2; break;
      case 'S' : Letter[d+2] = 2; Letter[d+3] = 114; d+=2; break;
      case 'T' : Letter[d+2] = 0; Letter[d+3] = 192; d+=2; break;
      //case 'U' : Letter[d+2] = 24; Letter[d+3] = 35; d+=2; break;
      case 'U' : Letter[d+2] = 10; Letter[d+3] = 42; d+=2; break;
      case 'V' : Letter[d+2] = 25; Letter[d+3] = 8; d+=2; break;
      case 'W' : Letter[d+2] = 25; Letter[d+3] = 7; d+=2; break;
      case 'X' : Letter[d+2] = 3; Letter[d+3] = 12; d+=2; break;
      case 'Y' : Letter[d+2] = 2; Letter[d+3] = 19; d+=2; break;
      case 'Z' : Letter[d+2] = 1; Letter[d+3] = 104; d+=2; break; 
      case '-' : Letter[d+2] = 4; Letter[d+3] = 0; d+=2; break; 
      case '+' : Letter[d+2] = 4; Letter[d+3] = 144; d+=2; break;
      case '=' : Letter[d+2] = 4; Letter[d+3] = 48; d+=2; break;
      case '/' : Letter[d+2] = 1; Letter[d+3] = 8; d+=2; break;
      case '%' : Letter[d+2] = 5; Letter[d+3] = 24; d+=2; break;
      case '\'' : Letter[d+2] = 0; Letter[d+3] = 8; d+=2; break;
      case '_' : Letter[d+2] = 0; Letter[d+3] = 32; d+=2; break; 
      case '(' : Letter[d+2] = 0; Letter[d+3] = 12; d+=2; break; 
      case ')' : Letter[d+2] = 3; Letter[d+3] = 0; d+=2; break;
      case '*' : Letter[d+2] = 7; Letter[d+3] = 28; d+=2; break;
      case '#' : Letter[d+2] = 31; Letter[d+3] = 255; d+=2; break;  //Dolu
    }
   } 
}
