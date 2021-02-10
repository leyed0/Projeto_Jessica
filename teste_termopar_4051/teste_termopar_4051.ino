#include "max6675.h" // max6675.h file is part of the library that you should download from Robojax.com

struct Multiplex_Signal
{
    uint8_t A, B, C, COM, SCK, EN[5];
    int Val;
};
//A,B,C,COM,EN0,1,2,3,4,5; - TOTAL 40 pins
struct CP{
  MAX6675 Thermal[5];
  int water[5];
  int moisture;
};

Multiplex_Signal CD;
//MAX6675 robojax(sckPin, csPin, soPin);// create instance object of MAX6675

MAX6675 robojax(8, 9, 10);// create instance object of MAX6675


void setup() {
  InitCD(A3,A4,A5,7, 11);
  Serial.begin(9600);// initialize serial monitor with 9600 baud
  Serial.println("Robojax MAX6675"); 

}

void loop() {
  for (int i = 0; i < 8; i++)
  {
      Serial.print(i); 
      Serial.print(" - C = ");
      Serial.println(GetCelcius(i));
      delay(0);
  }
  delay(1000);
  for (int i = 0; i < 10; i++)
  {
      Serial.println(' ');
  }
  
}
float GetCelcius(int val){
  digitalWrite(CD.A, bitRead(val, 0));
  digitalWrite(CD.B, bitRead(val, 1));
  digitalWrite(CD.C, bitRead(val, 2));
  digitalWrite(CD.EN[0], LOW);
  digitalWrite(CD.COM, LOW);
  float ret = robojax.readCelsius();
  digitalWrite(CD.EN[0], HIGH);
  digitalWrite(CD.COM, HIGH);
  return ret;
}
void InitCD(uint8_t a,uint8_t b, uint8_t c, uint8_t en, uint8_t com){
  CD.A = a;
  CD.B = b;
  CD.C = c;
  CD.EN[0] = en;
  CD.COM = com;
  pinMode(CD.A, OUTPUT);
  pinMode(CD.B, OUTPUT);
  pinMode(CD.C, OUTPUT);
  pinMode(CD.EN[0], OUTPUT);
  pinMode(CD.COM, OUTPUT);
  digitalWrite(CD.A, LOW);
  digitalWrite(CD.B, LOW);
  digitalWrite(CD.C, LOW);
  digitalWrite(CD.EN[0], HIGH);
  digitalWrite(CD.COM, HIGH);
}

void SetCd(int val){
  CD.Val = val;
  digitalWrite(CD.A, bitRead(val, 0));
  digitalWrite(CD.B, bitRead(val, 1));
  digitalWrite(CD.C, bitRead(val, 2));
}