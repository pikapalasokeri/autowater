#include "DigitalOutPin.hpp"

extern "C"
{
#include "ABElectronics_C_Libraries/IOPi/ABE_IoPi.h"
}

DigitalOutPin::DigitalOutPin(char adress,
			     int pinNumber,
			     std::mutex& globalPinCommunicationMutex)
  : adress_(adress),
    pinNumber_(pinNumber),
    globalPinCommunicationMutex_(globalPinCommunicationMutex)
{
  std::lock_guard<std::mutex> lock(globalPinCommunicationMutex_);
  set_pin_direction(adress_, pinNumber_, 0x00);
}

void
DigitalOutPin::writeHigh()
{
  std::lock_guard<std::mutex> lock(globalPinCommunicationMutex_);
  write_pin(adress_, pinNumber_, 1);
}

void
DigitalOutPin::writeLow()
{
  std::lock_guard<std::mutex> lock(globalPinCommunicationMutex_);
  write_pin(adress_, pinNumber_, 0);
}
