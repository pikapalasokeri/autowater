#include "AnalogInPin.hpp"
#include "ABElectronics_C_Libraries/ADCPi/ABE_ADCPi.h"

AnalogInPin::AnalogInPin(char address, char channel)
  : address_(address),
    channel_(channel),
    bitRate_(18),
    pga_(1),
    conversionMode_(0)
{}

double
AnalogInPin::readVoltage() const
{
  return read_voltage(address_, channel_, bitRate_, pga_, conversionMode_);
}
