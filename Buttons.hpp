#pragma once

#include <Arduino.h>
#include "src/MAX5160/DigiPot.hpp"
#include "CanDevice.hpp"

#define PRINT_BUTTONS

class Buttons : public CanDevice {
    enum Type {
        LEFT_SCROLL_UP,
        LEFT_SCROLL_CLICK,
        LEFT_SCROLL_DOWN,
        LEFT_UPPER_BTN,
        LEFT_LOWER_BTN,
        RIGHT_SCROLL_UP,
        RIGHT_SCROLL_DOWN,
        RIGHT_UPPER_BTN,
        RIGHT_LOWER_BTN
    };

    DigiPot* channel0;
    DigiPot* channel1;
        
    uint32_t timer = 0;
    const static uint8_t buttonCount = 9;
    bool status[buttonCount] = {};
    uint32_t activation[buttonCount] = {};

    static uint8_t frames[buttonCount][3];
    static uint8_t channels[buttonCount];
    static MAX5160::Resistance resistances[buttonCount];

#ifdef PRINT_BUTTONS
    static const char* names[buttonCount];
#endif

    void activate(uint8_t buttonId);
    void deactivate(uint8_t buttonId);

public:
    Buttons(DigiPot* channel0, DigiPot* channel1);
    void begin();
    bool parseFrame(Can::Frame* frame);
    void iterate();

#ifdef PRINT_BUTTONS
    void printButtons();
#endif
};