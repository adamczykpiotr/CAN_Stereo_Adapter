#pragma once

#include <Arduino.h>
#include "CanDevice.hpp"

class Handbrake : public CanDevice {
    uint8_t basePin;

public:
    Handbrake(uint8_t basePin);
    
    void begin();
    bool parseFrame(Can::Frame* frame);
};