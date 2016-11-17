#include "PinFactory.hpp"
#include "OutPin.hpp"

#include "ABElectronics_C_Libraries/IOPi/ABE_IoPi.h"

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
  PinFactory pinFactory;
  
  std::vector<OutPinPtr> pins;
  for (int i = 0; i < 16; ++i)
    pins.push_back(pinFactory.createOutPin(0x21, i));
    
  while (true)
  {
    setAllLow(pins);
    usleep(1000000);
    setAllHigh(pins);
    usleep(1000000);
  }

  return 0;
}
