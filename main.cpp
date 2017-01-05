#include "WateringUnitManager.hpp"
#include "WateringUnitConfigReader.hpp"
#include "PinHandler.hpp"

int main()
{
  PinHandler pinHandler;
  WateringUnitConfigReader configReader("config");
  WateringUnitManager manager(pinHandler, configReader);
  manager.run();

  return 0;
}
