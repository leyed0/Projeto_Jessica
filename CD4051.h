#pragma once
#include<arduino.h>

namespace LeyedLib{
    enum ArduinoPinModes{Output=0,Input=1,Input_PullUp=3};
    enum Pins{IO0=3,IO1=3<<2,IO2=3<<4,IO3=3<<6,IO4=3<<8,IO5=3<<10,IO6=3<<12,IO7=3<<14};
    class CD4051_IO{
        //uint8_t PIN[8];
        uint16_t PinModes;
        void SetPinModes(ArduinoPinModes md){
            PinModes = 0;
            PinModes = md||md<<2||md<<4||md<<6||md<<8||md<<10||md<<12||md<<14;
        };
        void SetPinModes(ArduinoPinModes[8]);
    };
    class CD4051{
        //the pins
        uint8_t A, B, C, EN, COM;
        CD4051_IO Pins;

        CD4051(uint8_t a, uint8_t b, uint8_t c, uint8_t en, uint8_t com){
            A = a;
            B = b;
            C = c;
            EN = en;
            COM = com;
        }
        void SetPins(){

        }
    };
}