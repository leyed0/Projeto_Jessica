#include "cd4051.hpp"
#include "max6675.h"
#include <SoftwareSerial.h>

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
int del=50;
LeyedLib::CD4051* CD;
MAX6675 *thermal;

probes PT[3] = {{0 ,1 , 2, 3, 4, 5, 6, 7, 8, 9,10},
                {11,12,13,14,15,16,17,18,19,20,21},
                {22,23,24,25,26,27,28,29,30,31,32}};

uint8_t cds[] = {A5, A4,A3,A2,A1};
void setup(){
    Serial.begin(115200);
    CD = new LeyedLib::CD4051(12,11,10,A0,cds,5);
    thermal = new MAX6675(9, CD->COM, 8);
}
//     A0 = IO
//     A1 = EN0
//     A2 = EN1
//     A3 = EN2
//     A4 = EN3
//     A5 = EN4

//     D12 = Multiplex A
//     D11 = Multiplex B
//     D10 = Multiplex C
//     D9 = Thermal SCK
//     D8 = Thermal SO

//     D3 = TX1
//     D2 = RX1

//ESP GPIO9 = TX
//ESP GPIO10 = RX - buffered
void loop(){
    int tempo = millis();
    readprobe(0);
    readprobe(1);
    readprobe(2);
    tempo=millis()-tempo;
    for (uint8_t j = 0; j < 3; j++)
    {
        Serial.print(j);
        Serial.print(": ");
        Serial.print("\t");
        for (uint8_t i = 0; i < 5; i++)
        {
            Serial.print(PT[j].Read.Thermal[i], 1);
            Serial.print("\t");
        }
        Serial.print(PT[j].Read.Continuity, BIN);
        Serial.print("\t");
        Serial.print(PT[j].Read.Moisture);
        Serial.print("\t ");
    }
    Serial.println();
}

void blink(uint8_t pin){
    
    digitalWrite(CD->SetIO(pin, LeyedLib::ArduinoPinModes::Output),LOW);
    digitalWrite(CD->COM, LOW);
    delay(del);
    digitalWrite(CD->COM, HIGH);
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