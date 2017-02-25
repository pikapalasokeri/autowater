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
    humidityValueThreshold_(config.inqHumidityThreshold()),
    interval_(config.inqInterval()),
    waitIterations_(config.inqWaitIterations()),
    name_(config.inqName())
{
  pumpControlPin_->writeLow();

  logger_ << "Creating watering unit with config: " << Logger::endl
	  << config << Logger::endl << Logger::endl << Logger::flush;
}

void
WateringUnit::run()
{
  logger_ << name_ << "::run" << Logger::endl << Logger::flush;
  double lastHumidityValue = 0.0;
  int iterationsSinceLastWatering = waitIterations_;
  
  while (true)
  {
    std::this_thread::sleep_for(std::chrono::seconds(interval_));

    const double humidityValue = getHumidityValue();
    
    logger_ << name_ << ": humidityValue: " << humidityValue << Logger::endl;
    
    if (lastHumidityValue < humidityValueThreshold_
	&& humidityValue < humidityValueThreshold_
	&& iterationsSinceLastWatering >= waitIterations_)
    {
      pumpControlPin_->writeHigh();
      iterationsSinceLastWatering = 0;
      logger_ << name_ << ": pump set to high." << Logger::endl;
    }
    else
    {
      pumpControlPin_->writeLow();
      ++iterationsSinceLastWatering;
      logger_ << name_ << ": pump set to low." << Logger::endl;
    }

    lastHumidityValue = humidityValue;
    logger_ << Logger::flush;
  }
}

double
WateringUnit::getHumidityValue() const
{
  double totalVoltage = 0.0;
  const int numAverageMeasurements = 8;
  for (int i = 0; i < numAverageMeasurements; ++i)
  {
    totalVoltage += humiditySensorPin_->readVoltage();
  }
  
  return totalVoltage/numAverageMeasurements;
}
