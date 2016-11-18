#ifndef OutPin_hpp
#define OutPin_hpp

#include <memory>

class PinHandler;

class OutPin
{
public:
  void writeHigh();
  void writeLow();

  OutPin(const OutPin&) = delete;
  OutPin& operator=(const OutPin&) = delete;
  
private:
  OutPin(char adress, int pinNumber);
  friend PinHandler;
  
  const char adress_;
  const int pinNumber_;
};

using OutPinPtr = std::shared_ptr<OutPin>;

#endif
