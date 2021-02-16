#include "cd4051.hpp"

struct probes
{
    const uint8_t Thermal[5],Continuity[5], Moisture;
};
int del=1;
LeyedLib::CD4051* CD;
uint8_t cds[] = {8, 9,10,11,12};
probes PT[3] = {{0 ,1 , 2, 3, 4, 5, 6, 7, 8, 9,10},
                {11,12,13,14,15,16,17,18,19,20,21},
                {22,23,24,25,26,27,28,29,30,31,32}};

void setup(){
    Serial.begin(9600);
    CD = new LeyedLib::CD4051(5,6,7,14,cds,5);
}
void loop(){
    for (uint8_t i = 0; i < ((8*3)+6); i++)
    {
        blink(i);
        delay(del);
    }
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