#include <arduino.h>
#include <SoftwareSerial.h>
#include "max6675.h"
#include <SoftwareSerial.h>
#include "cd4051.hpp"

struct readings{
    //uint8_t ID;
    uint8_t Continuity;
    uint8_t Moisture;
    //uint8_t chk;
    uint16_t Thermal[5];
};
struct probes
{
    const uint8_t Thermal[5],Continuity[5], Moisture;
    readings Read;
};

SoftwareSerial ESP(3,2);
int del=25, intervalo=1000;
LeyedLib::CD4051* CD;
MAX6675 *thermal;
probes PT[3] = {{0 ,1 , 2, 3, 4, 5, 6, 7, 8, 9,10},
                {11,12,13,14,15,16,17,18,19,20,21},
                {22,23,24,25,26,27,28,29,30,31,32}};

uint8_t cds[] = {A5, A4,A3,A2,A1};

void setup(){
    pinMode(7, OUTPUT);
    ESP.begin(115200);
    Serial.begin(115200);
    CD = new LeyedLib::CD4051(12,11,10,A0,cds,5);
    thermal = new MAX6675(9, CD->COM, 8);
    digitalWrite(7,LOW);
}

unsigned long tempo = millis();
void loop(){
    if(tempo+intervalo<=millis()){
        tempo+=intervalo;
        readprobe(0);
        readprobe(1);
        readprobe(2);
        SendData();
        Serial.println(millis());
        Serial.println(tempo);
        //Printdata();
    }
}

void readprobe(uint8_t pb){
    //PT[pb].Read.chk=0;
    for (int i = 0; i < 5; i++)
    {
        digitalWrite(CD->COM, HIGH);
        digitalWrite(CD->SetIO((i+(11*pb)), LeyedLib::ArduinoPinModes::Output),LOW);
        delay(del);
        PT[pb].Read.Thermal[i]=(uint16_t)(thermal->readCelsius()*100);
        //delay(del);
        CD->reset();
        //PT[pb].Read.chk+=PT[pb].Read.Thermal[i];
    }
    PT[pb].Read.Continuity=0;
    digitalWrite(7,HIGH);
    for (int i = 0; i < 5; i++)
    {
        digitalWrite(CD->SetIO(((i+5)+(11*pb)), LeyedLib::ArduinoPinModes::Input_PullUp),LOW);
        PT[pb].Read.Continuity|=digitalRead(CD->COM)<<i;
        CD->reset();
    }
    digitalWrite(7,LOW);
    //PT[pb].Read.chk+=PT[pb].Read.Continuity;
    digitalWrite(CD->SetIO(((10)+(11*pb)), LeyedLib::ArduinoPinModes::Input_Analog),LOW);
    PT[pb].Read.Moisture=map(analogRead(CD->COM),0,1023,0,255);
    CD->reset();
    //PT[pb].Read.chk+=PT[pb].Read.Moisture;
}

void SendData(){
    readings Reads[3];
    Reads[0] = PT[0].Read;
    Reads[1] = PT[1].Read;
    Reads[2] = PT[2].Read;
    const char* dp = (const char*) &Reads;

    ESP.print('W');
    //delay(50);
    for (int i = 0; i < (sizeof(Reads)); i++) ESP.write(*dp++);
}

void Printdata(){
  for (uint8_t j = 0; j < 3; j++)
    {
        Serial.print(j);
        Serial.print(": ");
        Serial.print("\t");
        for (uint8_t i = 0; i < 5; i++)
        {
            Serial.print((float)PT[j].Read.Thermal[i]/100, 1);
            Serial.print("\t");
        }
        Serial.print(PT[j].Read.Continuity, BIN);
        Serial.print("\t");
        Serial.print(PT[j].Read.Moisture);
        Serial.print("\t ");
    }
    Serial.println();
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