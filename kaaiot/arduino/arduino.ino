#include<arduino.h>
#include <SoftwareSerial.h>
#include"cd4051.hpp"

struct readings{
    float Thermal[5];
    uint8_t Continuity;
    int Moisture;
};

//SoftwareSerial ESP(2,3);
SoftwareSerial ESP(34,32);

struct mat{
    uint8_t a, b;
    uint16_t r;
    int Operator;
};

mat Mat;

void setup(){
    ESP.begin(115200);
    Serial.begin(115200);
    
    pinMode(28, OUTPUT);
    digitalWrite(28, LOW);
}



void loop(){
    Mat.a = random(1, 9);
    Mat.b = random(1, 9);
    Mat.Operator = random(0, 3);
    switch (Mat.Operator)
    {
    case 0:
        Mat.r = Mat.a+Mat.b;
        break;
    case 1:
        Mat.r = Mat.a-Mat.b;
        break;
    case 2:
        Mat.r = Mat.a*Mat.b;
        break;
    case 3:
        Mat.r = Mat.a/Mat.b;
        break;
    }
    const char* dp = (const char*) &Mat;
    for (int i = 0; i < sizeof(mat); i++) ESP.print(*dp++);

    
    Serial.print("Sent: ");
    Serial.print(Mat.a);
    Serial.print(Mat.Operator==0?"+":Mat.Operator==1?"-":Mat.Operator==2?"*":"/");
    Serial.print(Mat.b);
    Serial.print(" = ");
    Serial.print(Mat.r);
    Serial.println();
    delay(1000);
}