#include <ESP8266WiFi.h>
#include<SoftwareSerial.h>

//SoftwareSerial ARD(DD0, DD1);
SoftwareSerial ARD(5, 13);

void setup(){
    Serial.begin(115200);
    ARD.begin(115200);
}

int a, b, op, r, c;

void loop(){
    if(ARD.available()){
        a = ARD.read();
        b = ARD.read();
        op = ARD.read();
        r = ARD.read();

        
        Serial.print(a);
        Serial.print(op==0?" + ":op==1?" - ":op==2?" * ":" / ");
        Serial.print(b);
        Serial.print(" = ");
        Serial.println(r);
    }
}


//GPIO 5 = D1 = 5
//GPIO 13 = D7 = 13