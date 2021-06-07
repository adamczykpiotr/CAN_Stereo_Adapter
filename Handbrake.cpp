#include "Handbrake.hpp"

Handbrake::Handbrake(uint8_t basePin) {
    this->basePin = basePin;
}

void Handbrake::begin() {
    pinMode(this->basePin, OUTPUT);
}

bool Handbrake::parseFrame(Can::Frame* frame) {
    //validate frame id
    if(frame->id != 0x370) return false;

    bool active = (frame->data[1] == 0x01);
    digitalWrite(this->basePin, active);
    return true;
}