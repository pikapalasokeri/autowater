#include "DigitalOutPin.hpp"

extern "C"
{
#include "ABElectronics_C_Libraries/IOPi/ABE_IoPi.h"
}

DigitalOutPin::DigitalOutPin(char adress, int pinNumber)
  : adress_(adress),
    pinNumber_(pinNumber)
{
  set_pin_direction(adress_, pinNumber_, 0x00);
}

void
DigitalOutPin::writeHigh()
{
  write_pin(adress_, pinNumber_, 1);
}

void
DigitalOutPin::writeLow()
{
  write_pin(adress_, pinNumber_, 0);
}
