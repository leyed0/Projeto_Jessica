#include<SoftwareSerial.h>

SoftwareSerial ARD(3,2);

void setup(){
    ARD.begin(115200);
    Serial.begin(115200);
}

int a, b, op, r, c;
void loop(){
    a = random(1,9);
    b = random(1,9);
    op = random(0,4);
    switch (op)
    {
    case 0:
        r = a+b;
        break;
    case 1:
        r = a-b;
        break;
    case 2:
        r = a*b;
        break;
    case 3:
        r = a/b;
        break;
    
    default:
        break;
    }
    ARD.print(a);
    ARD.print(b);
    ARD.print(op);
    ARD.print(r);
    Serial.print(a);
    Serial.print(op==0?" + ":op==1?" - ":op==2?" * ":" / ");
    Serial.print(b);
    Serial.print(" = ");
    Serial.println(r);
    delay(200);
}