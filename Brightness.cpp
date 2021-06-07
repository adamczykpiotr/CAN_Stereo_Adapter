#include "Brightness.hpp"

Brightness::Brightness(uint8_t basePin, uint8_t threshold) {
    this->basePin = basePin;
    this->threshold = threshold;
}

void Brightness::begin() {
    pinMode(this->basePin, OUTPUT);
    digitalWrite(this->basePin, HIGH); //default day mode
}

bool Brightness::parseFrame(Can::Frame* frame) {
    //validate frame id
    if(frame->id != 0x235) return false;

    uint8_t level = frame->data[1];
    if(level == 0x00) level = 0xFF;

    bool nighMode = (level < this->threshold);
    digitalWrite(this->basePin, !nighMode);
    return true;
}