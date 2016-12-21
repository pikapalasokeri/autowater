#include "WateringUnit.hpp"

#include <iostream>
#include <chrono>
#include <thread>

WateringUnit::WateringUnit(DigitalOutPin* pumpControlPin,
			   AnalogInPin* humiditySensorPin)
  : pumpControlPin_(pumpControlPin),
    humiditySensorPin_(humiditySensorPin)
{}

void
WateringUnit::run()
{
  std::cout << "watering unit checking in!" << std::endl;
  while (true)
  {
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "still running..." << humiditySensorPin_ << std::endl;
    // check humidity
    // water if necessary
    // log
    // wait
  }
}
