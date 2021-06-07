#pragma once

#include <Arduino.h>
#include "CanDevice.hpp"

/*
    OUTPUT - NPN transistor
    digitalWrite(this->basePin, LOW)  - GND at the output, day mode
    digitalWrite(this->basePin, HIGH) - +12V at the output, night mode
*/

class Brightness : public CanDevice {
    uint8_t threshold;
    uint8_t basePin;

public:
    Brightness(uint8_t basePin, uint8_t threshold);
    
    void begin();
    bool parseFrame(Can::Frame* frame);
};