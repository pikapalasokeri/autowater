#include "WateringUnit.hpp"

#include "AnalogInPin.hpp"
#include "DigitalOutPin.hpp"

#include <iostream>
#include <chrono>
#include <thread>

WateringUnit::WateringUnit(DigitalOutPin* pumpControlPin,
			   AnalogInPin* humiditySensorPin,
			   double humidityThreshold)
  : pumpControlPin_(pumpControlPin),
    humiditySensorPin_(humiditySensorPin),
    humidityVoltageThreshold_(humidityThreshold*AnalogInPin::maxVoltage)
{
  pumpControlPin_->writeLow();
}

void
WateringUnit::run()
{
  std::cout << this << " ::run" << std::endl;
  double lastHumidityVoltage = 0.0;
  
  while (true)
  {
    std::this_thread::sleep_for(std::chrono::seconds(2));

    const double humidityVoltage = humiditySensorPin_->readVoltage();
    
    std::cout << this << " humidityVoltage: " << humidityVoltage << std::endl;
    
    if (lastHumidityVoltage < humidityVoltageThreshold_
	&& humidityVoltage < humidityVoltageThreshold_)
    {
      pumpControlPin_->writeHigh();
      std::cout << this << " pump set to high." << std::endl;
    }
    else
    {
      pumpControlPin_->writeLow();
      std::cout << this << " pump set to low." << std::endl;
    }
    
    lastHumidityVoltage = humidityVoltage;
  }
}
