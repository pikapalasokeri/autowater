#ifndef AnalogInPin_hpp
#define AnalogInPin_hpp

#include <memory>
#include <mutex>

class PinHandler;

class AnalogInPin
{
public:
  AnalogInPin(const AnalogInPin&) = delete;
  AnalogInPin& operator=(const AnalogInPin&) = delete;

  double readVoltage() const;

private:
  AnalogInPin(char adress,
	      char channel,
	      std::mutex& globalPinCommunicationMutex);
  friend PinHandler;

  const char adress_;
  const char channel_;
  const int bitRate_; // 12, 14, 16 or 18 according to header
                      // 17 is max according to web page
  const int pga_; // programmable gain amplifier
  const char conversionMode_; // 0 = one shot conversion, 1 = coninuous conversion
  std::mutex& globalPinCommunicationMutex_;
};

using AnalogInPinPtr = std::shared_ptr<AnalogInPin>;

#endif
