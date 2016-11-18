#include "PinHandler.hpp"

#include "OutPin.hpp"
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

OutPin*
PinHandler::createOutPin(char adress, int pinNumber)
{
  makeSureIsInitialized(adress);
  verify(adress, pinNumber);

  outPins_.emplace_back(new OutPin(adress, pinNumber));
  return outPins_.back().get();
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
