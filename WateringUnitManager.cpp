#include "WateringUnitManager.hpp"

#include "PinHandler.hpp"

WateringUnitManager::WateringUnitManager(PinHandler& pinHandler)
{
  createWateringUnits(pinHandler);
}

namespace
{
  void
  runWateringUnit(std::unique_ptr<WateringUnit>& wateringUnit)
  {
    wateringUnit->run();
  }
}

void
WateringUnitManager::run()
{
  for (std::unique_ptr<WateringUnit>& wateringUnit : wateringUnits_)
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
  const double humidityThreshold = 0.2;
  wateringUnits_.emplace_back(new WateringUnit(pinHandler.createDigitalOutPin(0x21, 1),
					       pinHandler.createAnalogInPin(0x68, 4),
					       humidityThreshold));
  wateringUnits_.emplace_back(new WateringUnit(pinHandler.createDigitalOutPin(0x21, 2),
					       pinHandler.createAnalogInPin(0x68, 3),
					       humidityThreshold));
  wateringUnits_.emplace_back(new WateringUnit(pinHandler.createDigitalOutPin(0x21, 3),
					       pinHandler.createAnalogInPin(0x68, 2),
						 humidityThreshold));
  wateringUnits_.emplace_back(new WateringUnit(pinHandler.createDigitalOutPin(0x21, 14),
					       pinHandler.createAnalogInPin(0x68, 1),
					       humidityThreshold));
}

