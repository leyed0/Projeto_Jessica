#include <ESP8266WiFi.h>
#include<SoftwareSerial.h>

SoftwareSerial ESP(DD0, DD1);

void setup(){
    Serial.begin(115200);
    ESP.begin(115200);
}

int a, b, op, r, c;

void loop(){
    if(ESP.available()){
        a = ESP.read();
        b = ESP.read();
        op = ESP.read();
        r = ESP.read();

        
        Serial.print(a);
        Serial.print(op==0?" + ":op==1?" - ":op==2?" * ":" / ");
        Serial.print(b);
        Serial.print(" = ");
        Serial.println(r);
    }
}