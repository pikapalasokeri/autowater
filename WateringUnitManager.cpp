#include "WateringUnitManager.hpp"

#include "PinHandler.hpp"
#include "WateringUnitConfigReader.hpp"

WateringUnitManager::WateringUnitManager(PinHandler& pinHandler, WateringUnitConfigReader& configReader)
  : configReader_(configReader)
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
  while (configReader_.parseNext())
  {
    wateringUnits_.emplace_back(new WateringUnit(pinHandler, configReader_.getConfig()));
  }
}

