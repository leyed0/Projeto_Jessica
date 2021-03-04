#include<SoftwareSerial.h>

// verde e amarelo
SoftwareSerial ESP(3,2);

struct mat{
    int a, b, op, r, c;
}Mat;

void setup(){
    ESP.begin(115200);
    Serial.begin(115200);
}

void loop(){
    Mat.a = random(1,9);
    Mat.b = random(1,9);
    Mat.op = random(0,4);
    switch (Mat.op)
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
    
    default:
        break;
    }
    SendData(Mat);
    Serial.print(Mat.a);
    Serial.print(Mat.op==0?" + ":Mat.op==1?" - ":Mat.op==2?" * ":" / ");
    Serial.print(Mat.b);
    Serial.print(" = ");
    Serial.println(Mat.r);
    delay(200);
}


void SendData(mat val){
    const char* dp = (const char*) &val;
    for (int i = 0; i < sizeof(mat); i++) ESP.print(*dp++);
}