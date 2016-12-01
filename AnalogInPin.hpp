#ifndef AnalogInPin_hpp
#define AnalogInPin_hpp

#include <memory>

class PinHandler;

class AnalogInPin
{
private:
  AnalogInPin(char adress, int pinNumber);
  friend PinHandler;

  const char adress_;
  const int pinNumber_;
};

using AnalogInPinPtr = std::shared_ptr<AnalogInPin>;

#endif
