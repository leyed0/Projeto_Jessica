#include <ESP8266WiFi.h>

void setup(){
    Serial.begin(115200);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
}

void loop(){
    for (int i = 0; i < 2; i++)
    {
        digitalWrite(2, bitRead(i, 0));
        Serial.print(bitRead(i, 0));
        Serial.println(digitalRead(3));
        delay(100);
    }
}