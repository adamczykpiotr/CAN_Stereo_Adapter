#pragma once
 
#include <Arduino.h>
#include "CanDevice.hpp"

class Reverse : public CanDevice {
    uint8_t basePin;

public:
    Reverse(uint8_t basePin);
    
    void begin();
    bool parseFrame(Can::Frame* frame);
};