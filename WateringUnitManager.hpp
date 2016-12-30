#ifndef WateringUnitManager_hpp
#define WateringUnitManager_hpp

#include "WateringUnit.hpp"

#include <memory>
#include <thread>
#include <vector>

class PinHandler;
class WateringUnitConfigReader;

class WateringUnitManager
{
public:
  WateringUnitManager(PinHandler&, WateringUnitConfigReader&);
  void run();
private:
  void createWateringUnits(PinHandler&);
  std::vector<std::unique_ptr<WateringUnit> > wateringUnits_;
  std::vector<std::unique_ptr<std::thread> > threads_;
  WateringUnitConfigReader& configReader_;
};


#endif
