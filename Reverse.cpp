#include "Reverse.hpp"

Reverse::Reverse(uint8_t basePin) {
    this->basePin = basePin;
}

void Reverse::begin() {
    pinMode(this->basePin, OUTPUT);
}

bool Reverse::parseFrame(Can::Frame* frame) {
    //validate frame id
    if(frame->id != 0x7FF) return false;

    bool active = (frame->data[1] == 0x01);
    digitalWrite(this->basePin, active);
    return true;
}