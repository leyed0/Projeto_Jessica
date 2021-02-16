#include<arduino.h>

void setup(){
    pinMode(A2, INPUT);
    Serial.begin(9600);
}

void loop(){
    int a2=0;
    for (int i = 0; i < 10; i++)
    {
        a2+=digitalRead(A2);
    }
    a2/=10;
    Serial.println(a2);
    delay(100);
}