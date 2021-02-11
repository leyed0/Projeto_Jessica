int sensor[5];

void setup(){
    for (int i = 0; i < 5; i++)
    {
        sensor[i]=i+2;
        pinMode(sensor[i], INPUT_PULLUP);
    }
    Serial.begin(9600);
}

void loop(){
    for (int i = 0; i < 5; i++)
    {
        Serial.print((digitalRead(sensor[i])?"OFF":"ON"));
        Serial.print(" - ");
    }
    Serial.println(" ");
    delay(100);
}