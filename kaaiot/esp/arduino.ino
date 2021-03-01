#include<arduino.h>
#include <SoftwareSerial.h>

//GPIO 10, 9
SoftwareSerial ARD(12,11);

void setup(){
    ARD.begin(115200);
    Serial.begin(115200);
}

void loop(){

}