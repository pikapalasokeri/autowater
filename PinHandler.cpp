#include "PinHandler.hpp"

#include "DigitalOutPin.hpp"
#include "AnalogInPin.hpp"
#include "ABElectronics_C_Libraries/IOPi/ABE_IoPi.h"
#include <memory>
#include <sstream>

#undef NDEBUG
#include <cassert>


bool PinHandler::alreadyCreated_ = false;

PinHandler::PinHandler()
{
  assert(!alreadyCreated_);
  alreadyCreated_ = true;
}

DigitalOutPin*
PinHandler::createDigitalOutPin(char adress, int pinNumber)
{
  makeSureIsInitialized(adress);
  verify(adress, pinNumber);

  digitalOutPins_.emplace_back(new DigitalOutPin(adress, pinNumber));
  return digitalOutPins_.back().get();
}

AnalogInPin*
PinHandler::createAnalogInPin(char adress, char pinNumber)
{
  makeSureIsInitialized(adress);
  verify(adress, pinNumber);

  analogInPins_.emplace_back(new AnalogInPin(adress, pinNumber));
  return nullptr;
}

void
PinHandler::verify(char adress, int pinNumber)
{
  IntSet& pinsAtThisAdress = occupiedAdressPins_[adress];
  auto insertionResult = pinsAtThisAdress.insert(pinNumber);
  const bool pinAlreadyInUse = !insertionResult.second;
  if (pinAlreadyInUse)
  {
    std::ostringstream os;
    os << "Pin at adress " << adress << " and pin number " << pinNumber << " already exists.";
    throw std::runtime_error(os.str());
  }
}

void
PinHandler::makeSureIsInitialized(char adress)
{
  if (occupiedAdressPins_.count(adress) == 0)
    IOPi_init(adress);
}
