#pragma once
#include<arduino.h>

namespace LeyedLib{
    enum ArduinoPinModes{Output=0,Input_Digital=1,Input_Analog=2,Input_PullUp=3};
    class CD4051{
        public:
        //the pins
        uint8_t A, B, C, *EN, COM, QTD;
        CD4051(uint8_t a, uint8_t b, uint8_t c, uint8_t com, uint8_t* en, uint8_t qtd){
            A = a;
            B = b;
            C = c;
            pinMode(A, OUTPUT);
            pinMode(B, OUTPUT);
            pinMode(C, OUTPUT);
            QTD = qtd;
            EN = new uint8_t[QTD];
            COM = com;
            Serial.println(QTD);
            for (int i = 0; i < QTD; i++)
            {
                EN[i]=en[i];
                pinMode(EN[i], OUTPUT);
            }
            reset();
        }

        void reset(){
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            for(int i=0;i<QTD;i++){
                digitalWrite(EN[i], HIGH);
            }
        }
        //OK
        //USE digitalWrite(SetIO(pin, mode), LOW);
        //Function that uses the pin
        //reset();
        uint8_t SetIO(uint8_t pin, ArduinoPinModes mode){
            digitalWrite(A, bitRead(pin, 0));
            digitalWrite(B, bitRead(pin, 1));
            digitalWrite(C, bitRead(pin, 2));
            switch (mode)
            {
            case ArduinoPinModes::Output:
                pinMode(COM, OUTPUT);
                break;
            case ArduinoPinModes::Input_PullUp:
                pinMode(COM, INPUT_PULLUP);
                break;
            case ArduinoPinModes::Input_Analog:
            case ArduinoPinModes::Input_Digital:
                pinMode(COM, INPUT);
                break;
            default:
                return -1;
                break;
            }
            return EN[pin/8];
        };
    };
}