#include "WateringUnit.hpp"

#include "AnalogInPin.hpp"
#include "DigitalOutPin.hpp"
#include "WateringUnitConfig.hpp"
#include "PinHandler.hpp"

#include <iostream>
#include <chrono>
#include <thread>

WateringUnit::WateringUnit(PinHandler& pinHandler, const WateringUnitConfig& config)
  : pumpControlPin_(pinHandler.createDigitalOutPin(config.inqPumpAdress(), config.inqPumpPin())),
    humiditySensorPin_(pinHandler.createAnalogInPin(config.inqSensorAdress(), config.inqSensorPin())),
    humidityVoltageThreshold_(config.inqHumidityThreshold()*AnalogInPin::maxVoltage),
    interval_(config.inqInterval()),
    name_(config.inqName())
{
  pumpControlPin_->writeLow();

  logger_ << "Creating watering unit with config: " << Logger::endl
	  << config << Logger::endl << Logger::endl << Logger::flush;
}

void
WateringUnit::run()
{
  logger_ << name_ << " ::run" << Logger::endl << Logger::flush;
  double lastHumidityVoltage = 0.0;
  
  while (true)
  {
    std::this_thread::sleep_for(std::chrono::seconds(interval_));

    const double humidityVoltage = humiditySensorPin_->readVoltage();
    
    logger_ << name_ << " humidityVoltage: " << humidityVoltage << Logger::endl;
    
    if (lastHumidityVoltage < humidityVoltageThreshold_
	&& humidityVoltage < humidityVoltageThreshold_)
    {
      pumpControlPin_->writeHigh();
      logger_ << name_ << " pump set to high." << Logger::endl;
    }
    else
    {
      pumpControlPin_->writeLow();
      logger_ << name_ << " pump set to low." << Logger::endl;
    }

    lastHumidityVoltage = humidityVoltage;
    logger_ << Logger::flush;
  }
}
