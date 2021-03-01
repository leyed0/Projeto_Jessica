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

SoftwareSerial UNO(3, 1);

readings Read[3];

void loop(){
    UNO.begin(115200);
    Serial.begin(115200);
}
int test;
void loop(){
    if(UNO.available){
        UNO.read(Read[0]);
    }
    Serial.println(Read[0].Thermal[0]);
}