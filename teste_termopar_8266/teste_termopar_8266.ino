#include <ESP8266WiFi.h>
#include "max6675.h" // max6675.h file is part of the library that you should download from Robojax.com

//////////////////////////////////////////////
//                 FUNCIONOU                //
//////////////////////////////////////////////

int soPin = 5;// SO=Serial Out
int csPin = 6;// CS = chip select CS pin
int sckPin = 7;// SCK = Serial Clock pin

//MAX6675 robojax(sckPin, csPin, soPin);// create instance object of MAX6675
//pinos do arduino 0, 1, 2
MAX6675 robojax1(16, 5, 4);// create instance object of MAX6675


void setup() {

          
  Serial.begin(9600);// initialize serial monitor with 9600 baud
  Serial.println("Robojax MAX6675"); 

}

void loop() {
  // basic readout test, just print the current temp
  // Robojax.com MAX6675 Temperature reading on Serial monitor
   Serial.print("1 - C = "); 
   Serial.println(robojax1.readCelsius());
   delay(1000);
}