#ifndef WateringUnitConfig_hpp
#define WateringUnitConfig_hpp

#include <string>

class WateringUnitConfig
{
public:
  WateringUnitConfig(char pumpAdress,
		     int pumpPin,
		     char sensorAdress,
		     int sensorPin,
		     double humidityThreshold,
		     int interval,
		     const std::string& name,
		     const std::string& logFilePath);
  char inqPumpAdress() const { return pumpAdress_; }
  int inqPumpPin() const { return pumpPin_; }
  char inqSensorAdress() const { return sensorAdress_; }
  int inqSensorPin() const { return sensorPin_; }
  double inqHumidityThreshold() const { return humidityThreshold_; }
  int inqInterval() const { return interval_; }
  std::string inqName() const { return name_; }
  std::string inqLogFilePath() const { return logFilePath_; }
private:
  char pumpAdress_;
  int pumpPin_;
  char sensorAdress_;
  int sensorPin_;
  double humidityThreshold_;
  int interval_;
  std::string name_;
  std::string logFilePath_;
};

std::ostream& operator<<(std::ostream& stream, const WateringUnitConfig& config);

#endif
