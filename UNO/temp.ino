// A0 - humidade

// GND ok
// VCC ok
// SCK 7
// SO 6

// CS:
// 	8 - primeiro
// 	9 - 2
// 	10 - 3
// 	11 - 4
// 	12 - 5

#include "max6675.h" // max6675.h file is part of the library that you should download from Robojax.com

//MAX6675 robojax(sckPin, csPin, soPin);// create instance object of MAX6675

MAX6675 robojax1(7, 8, 6);// create instance object of MAX6675
MAX6675 robojax2(7, 9, 6);// create instance object of MAX6675
MAX6675 robojax3(7, 10, 6);// create instance object of MAX6675
MAX6675 robojax4(7, 11, 6);// create instance object of MAX6675
MAX6675 robojax5(7, 12, 6);// create instance object of MAX6675
int humidity = A0
int time=1000;

void setup() {

          
  Serial.begin(9600);// initialize serial monitor with 9600 baud
  Serial.println("Inicializado!"); 

}


unsigned long timer = millis();
void loop() {
    
    if(timer+time<=millis()){
        timer+=time;
        log()
    }

}

void log(){
   Serial.print("sensores: \t")
   Serial.print(robojax1.readCelsius());
   Serial.print("\t");
   Serial.print(robojax2.readCelsius());
   Serial.print("\t");
   Serial.print(robojax3.readCelsius());
   Serial.print("\t");
   Serial.print(robojax4.readCelsius());
   Serial.print("\t");
   Serial.print(robojax5.readCelsius());
   Serial.print("\t");
   Serial.print(analogRead(humidity));
}