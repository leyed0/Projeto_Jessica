#include "max6675.h" // max6675.h file is part of the library that you should download from Robojax.com

int soPin = 5;// SO=Serial Out
int csPin = 6;// CS = chip select CS pin
int sckPin = 7;// SCK = Serial Clock pin

//MAX6675 robojax(sckPin, csPin, soPin);// create instance object of MAX6675

MAX6675 robojax1(2, 3, 4);// create instance object of MAX6675
MAX6675 robojax2(2, 5, 6);// create instance object of MAX6675
MAX6675 robojax3(2, 7, 8);// create instance object of MAX6675
MAX6675 robojax4(2, 9, 10);// create instance object of MAX6675
MAX6675 robojax5(2, 11, 12);// create instance object of MAX6675


void setup() {

          
  Serial.begin(9600);// initialize serial monitor with 9600 baud
  Serial.println("Robojax MAX6675"); 

}

void loop() {
  // basic readout test, just print the current temp
  // Robojax.com MAX6675 Temperature reading on Serial monitor
   Serial.print("1 - C = "); 
   Serial.print(robojax1.readCelsius());
   Serial.print(" F = ");
   Serial.println(robojax1.readFahrenheit());
   Serial.print("2 - C = "); 
   Serial.print(robojax2.readCelsius());
   Serial.print(" F = ");
   Serial.println(robojax2.readFahrenheit());
   Serial.print("3 - C = "); 
   Serial.print(robojax3.readCelsius());
   Serial.print(" F = ");
   Serial.println(robojax3.readFahrenheit());
   Serial.print("4 - C = "); 
   Serial.print(robojax4.readCelsius());
   Serial.print(" F = ");
   Serial.println(robojax4.readFahrenheit());
   Serial.print("5 - C = "); 
   Serial.print(robojax5.readCelsius());
   Serial.print(" F = ");
   Serial.println(robojax5.readFahrenheit());

             
   delay(1000);
}