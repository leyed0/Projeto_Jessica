#include "cd4051.hpp"
#include "max6675.h"

struct probes
{
    const uint8_t Thermal[5],Continuity[5], Moisture;
    int Readings[11];
};
int del=35;
LeyedLib::CD4051* CD;
MAX6675 *thermal;
uint8_t cds[] = {A1, A2,A3,A4,A5};
probes PT[3] = {{0 ,1 , 2, 3, 4, 5, 6, 7, 8, 9,10},
                {11,12,13,14,15,16,17,18,19,20,21},
                {22,23,24,25,26,27,28,29,30,31,32}};

void setup(){
    Serial.begin(9600);
    CD = new LeyedLib::CD4051(12,11,10,A0,cds,5);
}
void loop(){
    readprobe(0);
    for (uint8_t i = 0; i < 11; i++)
    {
        Serial.print(PT[0].Readings[i]);
        Serial.print(" - ");
    }
    Serial.println();
    // pinMode(10, OUTPUT);
    // digitalWrite(10, HIGH);
    // delay(1000);
    // digitalWrite(10, LOW);
    // delay(1000);
    // digitalWrite(10, HIGH);
    // delay(1000);
    // digitalWrite(10, LOW);
    // delay(1000);
}

void blink(uint8_t pin){
    
    digitalWrite(CD->SetIO(pin, LeyedLib::ArduinoPinModes::Output),LOW);
    digitalWrite(CD->COM, LOW);
    delay(del);
    digitalWrite(CD->COM, HIGH);
    CD->reset();
}

void readprobe(uint8_t pb){
    thermal = new MAX6675(9, CD->COM, 8);
    for (int i = 0; i < 5; i++)
    {
        
        digitalWrite(CD->COM, HIGH);
        digitalWrite(CD->SetIO((i+(13*pb)), LeyedLib::ArduinoPinModes::Output),LOW);
        delay(del);
        PT[pb].Readings[i]=thermal->readCelsius();
        CD->reset();
        
        // digitalWrite(CD->COM, HIGH);
        // digitalWrite(CD->SetIO((i+(13*pb)), LeyedLib::ArduinoPinModes::Output),LOW);
        // delay(del);
        // PT[pb].Readings[i]=thermal->readCelsius();
        // CD->reset();
    }
    delete thermal;
    for (int i = 5; i < 10; i++)
    {
        digitalWrite(CD->SetIO((i+(13*pb)), LeyedLib::ArduinoPinModes::Input_PullUp),LOW);
        PT[pb].Readings[i]=digitalRead(CD->COM);
        CD->reset();

    }
    digitalWrite(CD->SetIO((10*(pb+1)), LeyedLib::ArduinoPinModes::Input_Analog),LOW);
    PT[pb].Readings[10]=analogRead(CD->COM);
    CD->reset();
}