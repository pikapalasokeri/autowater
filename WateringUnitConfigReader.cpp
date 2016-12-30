#include "WateringUnitConfigReader.hpp"

#include <sstream>
#include <iostream>
#include <stdexcept>

WateringUnitConfigReader::WateringUnitConfigReader(const std::string& filePath)
  : configFileStream_(filePath)
{}

namespace
{
  bool in(const std::string& line, const std::string& subString)
  {
    return line.find(subString) != std::string::npos;
  }
}

bool
WateringUnitConfigReader::parseNext()
{
  clearCurrentEntry();
  
  bool shouldRead = false;
  std::string line;
  while (std::getline(configFileStream_, line))
  {
    if (in(line, "{"))
    {
      // we have found a new config entry
      shouldRead = true;
      continue;
    }
    if (in(line, "}"))
    {
      createCurrentConfig();
      return true;
    }

    if (shouldRead)
    {
      extractValueFromCurrentLine(line);
    }	
  }
  return false;
}

void
WateringUnitConfigReader::clearCurrentEntry()
{
  pumpAdress_ = boost::none;
  pumpPin_ = boost::none;
  sensorAdress_ = boost::none;
  sensorPin_ = boost::none;
  humidityThreshold_ = boost::none;
  interval_ = boost::none;
  name_ = boost::none;
  logFilePath_ = boost::none;
  currentConfig_ = boost::none;
}

void
WateringUnitConfigReader::extractValueFromCurrentLine(const std::string& line)
{
  if (!in(line, "="))
  {
    return;
  }

  const size_t delimiterIx = line.find("=");
  const std::string type(line.substr(0,delimiterIx));
  const std::string value(line.substr(delimiterIx+1, line.size()));
  if (type == "name")
  {
    name_ = value;
  }
  else if (type == "logfile")
  {
    logFilePath_ = value;
  }
  else
  {
    std::istringstream valueStream(value);
    if (type == "pump_adress")
    {
      int tmp;
      valueStream >> std::hex >> tmp;
      pumpAdress_ = tmp;
    }
    else if (type == "pump_pin")
    {
      pumpPin_ = 0;
      valueStream >> *pumpPin_;
    }
    else if (type == "sensor_adress")
    {
      int tmp;
      valueStream >> std::hex >> tmp;
      sensorAdress_ = tmp;
    }
    else if (type == "sensor_pin")
    {
      sensorPin_ = 0;
      valueStream >> *sensorPin_;
    }
    else if (type == "humidity_threshold")
    {
      humidityThreshold_ = 0.0;
      valueStream >> *humidityThreshold_;
      if (*humidityThreshold_ < 0.0)
      {
	throw std::runtime_error("Humidity threshold must not be negative.");
      }
    }
    else if (type == "interval")
    {
      interval_ = -1;
      valueStream >> *interval_;
      if (*interval_ < 1)
      {
	throw std::runtime_error("Interval must be 1 or greater.");
      }
    }
    else
    {
      throw std::runtime_error("Unrecognized property name '" + type);
    }	
  }
}

void
WateringUnitConfigReader::createCurrentConfig()
{
  currentConfig_ = WateringUnitConfig(*pumpAdress_,
				      *pumpPin_,
				      *sensorAdress_,
				      *sensorPin_,
				      *humidityThreshold_,
				      *interval_,
				      *name_,
				      *logFilePath_);
}

WateringUnitConfig
WateringUnitConfigReader::getConfig() const
{
  if (!currentConfig_)
  {
    throw std::runtime_error("Watering unit config not complete.");
  }
  return *currentConfig_;
}
