#include<arduino.h>
#include <SoftwareSerial.h>
#include"cd4051.hpp"

SoftwareSerial ESP(2,3);

void setup(){
    ESP.begin(115200);
}

void loop(){

}