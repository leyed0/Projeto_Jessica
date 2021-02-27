#include "cd4051.hpp"
#include "max6675.h"


struct readings{
    float Thermal[5];
    uint8_t Continuity;
    int Moisture;
};

struct probes
{
    const uint8_t Thermal[5],Continuity[5], Moisture;
    readings Read;
};
int del=500;
LeyedLib::CD4051* CD;
MAX6675 *thermal;
uint8_t cds[] = {A5, A4,A3,A2,A1};
probes PT[3] = {{0 ,1 , 2, 3, 4, 5, 6, 7, 8, 9,10},
                {11,12,13,14,15,16,17,18,19,20,21},
                {22,23,24,25,26,27,28,29,30,31,32}};

void setup(){
    Serial.begin(115200);
    CD = new LeyedLib::CD4051(12,11,10,A0,cds,5);
    thermal = new MAX6675(8, CD->COM, 9);
}
void loop(){
    blink(39);
}

void blink(uint8_t pin){
    
    digitalWrite(CD->SetIO(pin, LeyedLib::ArduinoPinModes::Output),LOW);
    digitalWrite(CD->COM, LOW);
    delay(del);
    digitalWrite(CD->COM, HIGH);
    delay(del);
    CD->reset();
}



void readprobe(uint8_t pb){
    for (int i = 0; i < 5; i++)
    {
        digitalWrite(CD->COM, HIGH);
        digitalWrite(CD->SetIO((i+(11*pb)), LeyedLib::ArduinoPinModes::Output),LOW);
        delay(del);
        PT[pb].Read.Thermal[i]=thermal->readCelsius();
        CD->reset();
    }
    PT[pb].Read.Continuity=0;
    for (int i = 0; i < 5; i++)
    {
        digitalWrite(CD->SetIO(((i+5)+(11*pb)), LeyedLib::ArduinoPinModes::Input_PullUp),LOW);
        PT[pb].Read.Continuity|=digitalRead(CD->COM)<<i;
        CD->reset();
    }
    digitalWrite(CD->SetIO(((10)+(11*pb)), LeyedLib::ArduinoPinModes::Input_Analog),LOW);
    PT[pb].Read.Moisture=analogRead(CD->COM);
    CD->reset();
    
}