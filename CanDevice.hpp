#pragma once

#include "src/CAN/CanBus.hpp"

class CanDevice {
   public:
      virtual void begin() = 0;
      virtual bool parseFrame(Can::Frame* frame) = 0;
};