#include "WateringUnitManager.hpp"
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

void
printVoltages(const std::vector<AnalogInPin*> pins)
{
  for (auto pin : pins)
    std::cout << pin->readVoltage() << std::endl;
  std::cout << std::endl;
}

int main()
{
  PinHandler pinHandler;
  WateringUnitManager manager(pinHandler);
  manager.run();
  /*
  std::vector<DigitalOutPin*> outPins;
  for (int i = 0; i < 16; ++i)
    outPins.push_back(pinHandler.createDigitalOutPin(0x21, i));

  std::vector<AnalogInPin*> inPins;
  for (int i = 0; i < 4; ++i)
    inPins.push_back(pinHandler.createAnalogInPin(0x68, i));
    
  while (true)
  {
    setAllLow(outPins);
    usleep(1000000);
    setAllHigh(outPins);
    usleep(1000000);

    printVoltages(inPins);
  }
  */

  return 0;
}
