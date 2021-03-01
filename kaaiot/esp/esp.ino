#include<arduino.h>
#include <SoftwareSerial.h>

struct mat{
    uint8_t a, b;
    uint16_t r;
    int Operator;
};

//GPIO 10, 9
//SoftwareSerial ARD(12,11);
SoftwareSerial ARD(3,4);

void setup(){
    ARD.begin(115200);
    Serial.begin(115200);
}
mat Mat;
void loop(){
    if (ARD.available()>=sizeof(mat))
    {
        char* dp = (char*) &Mat;
        for (int i = 0; i < sizeof(mat); i++) *dp++ = ARD.read(); 
        ARD.read();

            
        Serial.print("Received: ");
        Serial.print(Mat.a);
        Serial.print(Mat.Operator==0?"+":Mat.Operator==1?"-":Mat.Operator==2?"*":"/");
        Serial.print(Mat.b);
        Serial.print(" = ");
        Serial.print(Mat.r);
        Serial.println();
    }
}