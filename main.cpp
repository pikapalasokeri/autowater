#include "PinHandler.hpp"
#include "DigitalOutPin.hpp"

#include "ABElectronics_C_Libraries/IOPi/ABE_IoPi.h"

#include <iostream>
#include <unistd.h>
#include <vector>

void
setAllHigh(std::vector<DigitalOutPin*> pins)
{
  for (auto pin : pins)
    pin->writeHigh();
}

void
setAllLow(std::vector<DigitalOutPin*> pins)
{
  for (auto pin : pins)
    pin->writeLow();
}

int main()
{
  PinHandler pinHandler;
  
  std::vector<DigitalOutPin*> pins;
  for (int i = 0; i < 16; ++i)
    pins.push_back(pinHandler.createDigitalOutPin(0x21, i));
    
  while (true)
  {
    setAllLow(pins);
    usleep(1000000);
    setAllHigh(pins);
    usleep(1000000);
  }

  return 0;
}
