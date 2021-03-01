
void setup(){
    Serial.begin(115200);
    pinMode(3, OUTPUT);
    pinMode(2, INPUT);
}

void loop(){
    for (int i = 0; i < 2; i++)
    {
        digitalWrite(3, bitRead(i, 0));
        Serial.print(bitRead(i, 0));
        Serial.println(digitalRead(2));
        delay(100);
    }
}