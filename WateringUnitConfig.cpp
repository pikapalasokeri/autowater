#include "WateringUnitConfig.hpp"

#include <iostream>

WateringUnitConfig::WateringUnitConfig(char pumpAdress,
				       int pumpPin,
				       char sensorAdress,
				       int sensorPin,
				       double humidityThreshold,
				       int interval,
				       int waitIterations,
				       const std::string& name,
				       const std::string& logFilePath)
  : pumpAdress_(pumpAdress),
    pumpPin_(pumpPin),
    sensorAdress_(sensorAdress),
    sensorPin_(sensorPin),
    humidityThreshold_(humidityThreshold),
    interval_(interval),
    waitIterations_(waitIterations),
    name_(name),
    logFilePath_(logFilePath)
{}

std::ostream& operator<<(std::ostream& stream, const WateringUnitConfig& config)
{
  stream << "Name: " << config.inqName() << std::endl
	 << "Log file path: " << config.inqLogFilePath() << std::endl
	 << "Pump adress: " << std::hex << int(config.inqPumpAdress()) << std::dec << std::endl
	 << "Pump pin: " << config.inqPumpPin() << std::endl
	 << "Sensor adress: " << std::hex << int(config.inqSensorAdress()) << std::dec << std::endl
	 << "Sensor pin: " << config.inqSensorPin() << std::endl
	 << "Humidity threshold: " << config.inqHumidityThreshold() << std::endl
	 << "Interval: " << config.inqInterval() << std::endl
	 << "Wait iterations: " << config.inqWaitIterations() << std::endl;
  return stream;
}
