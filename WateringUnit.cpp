#include "WateringUnit.hpp"

WateringUnit::WateringUnit(DigitalOutPin* pumpControlPin,
			   AnalogInPin* humiditySensorPin)
  : pumpControlPin_(pumpControlPin),
    humiditySensorPin_(humiditySensorPin)
{}
