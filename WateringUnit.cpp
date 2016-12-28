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
  logger_ << this << " ::run" << Logger::endl << Logger::flush;
  double lastHumidityVoltage = 0.0;
  
  while (true)
  {
    std::this_thread::sleep_for(std::chrono::seconds(2));

    const double humidityVoltage = humiditySensorPin_->readVoltage();
    
    logger_ << this << " humidityVoltage: " << humidityVoltage << Logger::endl;
    
    if (lastHumidityVoltage < humidityVoltageThreshold_
	&& humidityVoltage < humidityVoltageThreshold_)
    {
      pumpControlPin_->writeHigh();
      logger_ << this << " pump set to high." << Logger::endl;
    }
    else
    {
      pumpControlPin_->writeLow();
      logger_ << this << " pump set to low." << Logger::endl;
    }

    lastHumidityVoltage = humidityVoltage;
    logger_ << Logger::flush;
  }
}
