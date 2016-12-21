#ifndef WateringUnitManager_hpp
#define WateringUnitManager_hpp

#include "WateringUnit.hpp"

#include <memory>
#include <thread>
#include <vector>

class PinHandler;

class WateringUnitManager
{
public:
  WateringUnitManager(PinHandler&);
  void run();
private:
  void createWateringUnits(PinHandler&);
  std::vector<WateringUnit> wateringUnits_;
  std::vector<std::unique_ptr<std::thread> > threads_;
};


#endif
