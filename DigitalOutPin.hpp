#ifndef DigitalOutPin_hpp
#define DigitalOutPin_hpp

#include <memory>

class PinHandler;

class DigitalOutPin
{
public:
  void writeHigh();
  void writeLow();

  DigitalOutPin(const DigitalOutPin&) = delete;
  DigitalOutPin& operator=(const DigitalOutPin&) = delete;
  
private:
  DigitalOutPin(char adress, int pinNumber);
  friend PinHandler;
  
  const char adress_;
  const int pinNumber_;
};

using DigitalOutPinPtr = std::shared_ptr<DigitalOutPin>;

#endif
