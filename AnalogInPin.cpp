#include "AnalogInPin.hpp"

extern "C"
{
#include "ABElectronics_C_Libraries/ADCPi/ABE_ADCPi.h"
}

const double AnalogInPin::maxVoltage = 5.0;
  
AnalogInPin::AnalogInPin(char address,
                         char channel,
                         std::mutex& globalPinCommunicationMutex)
  : address_(address),
    channel_(channel),
    bitRate_(18),
    pga_(1),
    conversionMode_(0),
    globalPinCommunicationMutex_(globalPinCommunicationMutex)
{}

double
AnalogInPin::readVoltage() const
{
  std::lock_guard<std::mutex> lock(globalPinCommunicationMutex_);
  return read_voltage(address_, channel_, bitRate_, pga_, conversionMode_);
}
