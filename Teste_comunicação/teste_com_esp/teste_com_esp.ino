#include <ESP8266WiFi.h>
#include<SoftwareSerial.h>
// branco e cinza
// SoftwareSerial ARD(DD0, DD1);

struct mat{
    uint8_t a, b, op, r, c;
}Mat;

//Serial é marrom e vermelho
void setup(){
    Serial.begin(115200);
}

void loop(){
    if(ReceiveData()){
        Serial.print("received: ");
        Serial.print(Mat.a);
        Serial.print(Mat.op==0?" + ":Mat.op==1?" - ":Mat.op==2?" * ":" / ");
        Serial.print(Mat.b);
        Serial.print(" = ");
        Serial.println(Mat.r);
    }
}

bool ReceiveData(){
  if (Serial.available()>=sizeof(mat))
    {
        char* dp = (char*) &Mat;
        for (int i = 0; i < sizeof(mat); i++) *dp++ = Serial.read();
        Serial.read();
        return true;
    }
    return false;
}
void SendData(){
    const char* dp = (const char*) &Mat;
    for (int i = 0; i < sizeof(mat); i++) ESP.print(*dp++);
}
//GPIO 5 = D1 = 5
//GPIO 13 = D7 = 13