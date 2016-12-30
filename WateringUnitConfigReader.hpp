#ifndef WateringUnitConfigReader_hpp
#define WateringUnitConfigReader_hpp

#include "WateringUnitConfig.hpp"

#include <fstream>
#include <memory>
#include <boost/optional.hpp>

class WateringUnitConfigReader
{
public:
  WateringUnitConfigReader(const std::string& configFilePath);
  bool parseNext();
  WateringUnitConfig getConfig() const;
private:
  void clearCurrentEntry();
  void extractValueFromCurrentLine(const std::string& line);
  void createCurrentConfig();

  boost::optional<WateringUnitConfig> currentConfig_;
  boost::optional<char> pumpAdress_;
  boost::optional<int> pumpPin_;
  boost::optional<char> sensorAdress_;
  boost::optional<int> sensorPin_;
  boost::optional<double> humidityThreshold_;
  boost::optional<int> interval_;
  boost::optional<std::string> name_;
  boost::optional<std::string> logFilePath_;
    
  std::ifstream configFileStream_;
};

#endif
