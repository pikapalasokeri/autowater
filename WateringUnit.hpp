#ifndef WateringUnit_hpp
#define WateringUnit_hpp

#include "Logger.hpp"

class DigitalOutPin;
class AnalogInPin;
class PinHandler;
class WateringUnitConfig;

class WateringUnit
{
public:
  WateringUnit(PinHandler&, const WateringUnitConfig&);
  void run();
private:
  double getHumidityValue() const;
  
  DigitalOutPin* const pumpControlPin_;
  AnalogInPin* const humiditySensorPin_;
  const double humidityValueThreshold_;
  const int interval_;
  const int waitIterations_;
  const std::string name_;
  Logger logger_;
};

#endif
