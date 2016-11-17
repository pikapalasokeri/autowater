
#include "ABElectronics_C_Libraries/IOPi/ABE_IoPi.h"

#include "OutPin.hpp"

#include <iostream>
#include <unistd.h>
#include <vector>

void
setAllHigh(std::vector<OutPinPtr> pins)
{
  for (auto pin : pins)
    pin->writeHigh();
}

void
setAllLow(std::vector<OutPinPtr> pins)
{
  for (auto pin : pins)
    pin->writeLow();
}

int main()
{
  IOPi_init(0x21);

  std::vector<OutPinPtr> pins;
  for (int i = 0; i < 16; ++i)
    pins.push_back(OutPinPtr(new OutPin(0x21, i)));
  
  while (true)
  {
    setAllLow(pins);
    usleep(1000000);
    setAllHigh(pins);
    usleep(1000000);
  }

  return 0;
}
