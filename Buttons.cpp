#include "Buttons.hpp"

uint8_t Buttons::frames[][3] = {
    {0x10, 0x1F, 0x00}, //LEFT_SCROLL_UP
    {0x30, 0x00, 0x00}, //LEFT_SCROLL_CLICK
    {0x20, 0x01, 0x00}, //LEFT_SCROLL_DOWN
    {0x40, 0x00, 0x00}, //LEFT_UPPER_BTN    [Source]
    {0x50, 0x00, 0x00}, //LEFT_LOWER_BTN    [Phone]
    {0x01, 0x00, 0x01}, //RIGHT_SCROLL_UP   [VOL+]
    {0x02, 0x00, 0x1F}, //RIGHT_SCROLL_DOWN [VOL-]
    {0x04, 0x00, 0x00}, //RIGHT_UPPER_BTN   [NEXT]
    {0x05, 0x00, 0x00}, //RIGHT_LOWER_BTN   [PREV]
};

uint8_t Buttons::channels[] = {
    0, 0, 0, 0, 0,
    0, 1, 1, 1
};

MAX5160::Resistance Buttons::resistances[] = {
    MAX5160::Resistance::R570, //NOT IN USE
    MAX5160::Resistance::R570, //NOT IN USE
    MAX5160::Resistance::R570, //NOT IN USE

    MAX5160::Resistance::R570,
    MAX5160::Resistance::R2K,
    MAX5160::Resistance::R3K6,

    MAX5160::Resistance::R2K,
    MAX5160::Resistance::R3K6,
    MAX5160::Resistance::R5K2,
};

Buttons::Buttons(DigiPot* channel0, DigiPot* channel1) {
    this->channel0 = channel0;
    this->channel1 = channel1;
}

void Buttons::begin() {
    this->channel0->begin();
    this->channel1->begin();
}

void Buttons::activate(uint8_t buttonId) {
    DigiPot* potentiometer = (Buttons::channels[buttonId] == 0)
        ? this->channel0
        : this->channel1;
    potentiometer->set(Buttons::resistances[buttonId]);

    this->status[buttonId] = true;
    this->activation[buttonId] = millis();

    #ifdef PRINT_BUTTONS
        Serial.print("Activated button:\t");
        Serial.println(Buttons::names[buttonId]);
    #endif
}

void Buttons::deactivate(uint8_t buttonId) {
    DigiPot* potentiometer = (Buttons::channels[buttonId] == 0)
        ? this->channel0
        : this->channel1
    ;
    potentiometer->disable();

    this->status[buttonId] = false;
    this->activation[buttonId] = 0;

    #ifdef PRINT_BUTTONS
        Serial.print("Deactivated button:\t");
        Serial.println(Buttons::names[buttonId]);
    #endif
}

/**
 * Attempts to parse Can::Frame to determine button press
 *
 * @param Can::Frame frame
 */
bool Buttons::parseFrame(Can::Frame* frame) {
    //validate frame id
    if(frame->id != 0x175) return false;

    //iterate over all possible buttons
    for(uint8_t i = 0; i < Buttons::buttonCount; i++ ) {
       
        //find match
        if( memcmp(frame->data + 5, Buttons::frames[i], 3) == 0 ) {
            this->activate(i);
            return true;
        }
    }
    
    return false;
}

/**
 * Iterates over buttons to disable buttons
 * not re-enabled after 150ms
 */
void Buttons::iterate() {
    if( millis() - this->timer < 5) return;
    this->timer = millis();

    for(uint8_t i = 0; i < Buttons::buttonCount; i++ ) {
        if(!this->status[i]) continue;

        if(millis() - activation[i] > 150) {
            this->deactivate(i);
        }
    }
}

#ifdef PRINT_BUTTONS

const char * Buttons::names[] = { 
    "LEFT_SCROLL_UP",
    "LEFT_SCROLL_CLICK",
    "LEFT_SCROLL_DOWN",
    "LEFT_UPPER_BTN",
    "LEFT_LOWER_BTN",
    "RIGHT_SCROLL_UP",
    "RIGHT_SCROLL_DOWN",
    "RIGHT_UPPER_BTN",
    "RIGHT_LOWER_BTN"
};

/**
 * Visualizes current state of all buttons
 */
void Buttons::printButtons() {
    for(uint8_t i = 0; i < Buttons::buttonCount; i++ ) {
        Serial.print(Buttons::names[i]);
        Serial.print(" :\t");
        Serial.println(this->status[i] ? " ON" : "OFF");
    }

    Serial.println("\033[0;0H");
    Serial.flush();
}
#endif