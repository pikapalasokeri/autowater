#include "WateringUnitManager.hpp"

#include "PinHandler.hpp"

WateringUnitManager::WateringUnitManager(PinHandler& pinHandler)
{
  createWateringUnits(pinHandler);
}

namespace
{
  void
  runWateringUnit(WateringUnit& wateringUnit)
  {
    wateringUnit.run();
  }
}

void
WateringUnitManager::run()
{
  for (WateringUnit& wateringUnit : wateringUnits_)
  {
    threads_.emplace_back(new std::thread(runWateringUnit, std::ref(wateringUnit)));
  }

  for (auto& thread : threads_)
  {
    thread->join();
  }
}

void
WateringUnitManager::createWateringUnits(PinHandler& pinHandler)
{
  for (int i = 0; i < 4; ++i)
  {
    wateringUnits_.push_back(WateringUnit(pinHandler.createDigitalOutPin(0x21, i),
					  pinHandler.createAnalogInPin(0x68, i)));
  }
}

