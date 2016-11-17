#include "OutPin.hpp"
#include "ABElectronics_C_Libraries/IOPi/ABE_IoPi.h"

OutPin::OutPin(char adress, int pinNumber)
  : adress_(adress),
    pinNumber_(pinNumber)
{
  set_port_direction(adress_, pinNumber_, 0x00);
}

void
OutPin::writeHigh()
{
  write_pin(adress_, pinNumber_, 1);
}

void
OutPin::writeLow()
{
  write_pin(adress_, pinNumber_, 0);
}
