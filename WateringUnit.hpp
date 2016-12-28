#ifndef WateringUnit_hpp
#define WateringUnit_hpp

#include "Logger.hpp"

class DigitalOutPin;
class AnalogInPin;

class WateringUnit
{
public:
  WateringUnit(DigitalOutPin*, AnalogInPin*, double humidityThreshold);
  void run();
private:
  DigitalOutPin* const pumpControlPin_;
  AnalogInPin* const humiditySensorPin_;
  const double humidityVoltageThreshold_;
  Logger logger_;
};

#endif
