#include "AnalogInPin.hpp"

extern "C"
{
#include "ABElectronics_C_Libraries/ADCPi/ABE_ADCPi.h"
}

AnalogInPin::AnalogInPin(char adress,
                         char channel,
                         std::mutex& globalPinCommunicationMutex)
  : adress_(adress),
    channel_(channel),
    bitRate_(18),
    pga_(1),
    conversionMode_(1),
    globalPinCommunicationMutex_(globalPinCommunicationMutex)
{}

double
AnalogInPin::readVoltage() const
{
  std::lock_guard<std::mutex> lock(globalPinCommunicationMutex_);
  return read_voltage(adress_, channel_, bitRate_, pga_, conversionMode_);
}
