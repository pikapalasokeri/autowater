#ifndef OutPin_hpp
#define OutPin_hpp

#include <memory>

class OutPin
{
public:
  OutPin(char adress, int pinNumber);

  void writeHigh();
  void writeLow();
  
  OutPin(const OutPin&) = delete;
  OutPin& operator=(const OutPin&) = delete;
  
private:
  const char adress_;
  const int pinNumber_;
};

using OutPinPtr = std::shared_ptr<OutPin>;

#endif
