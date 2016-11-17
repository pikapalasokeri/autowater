#include "PinFactory.hpp"

#include "OutPin.hpp"
#include "ABElectronics_C_Libraries/IOPi/ABE_IoPi.h"
#include <memory>

#undef NDEBUG
#include <cassert>


bool PinFactory::alreadyCreated_ = false;

PinFactory::PinFactory()
{
  assert(!alreadyCreated_);
  alreadyCreated_ = true;
}

OutPinPtr
PinFactory::createOutPin(char adress, int pinNumber)
{
  makeSureIsInitialized(adress);
  if (verify(adress, pinNumber))
    return OutPinPtr();

  // make_shared is supposedly better idiom to use for a number
  // of reasons, but restriction creation of OutPinPtrs via friend
  // is out of the question in that case. One has to use
  // inheritance hack instead.
  //  return std::make_shared<OutPin>(adress, pinNumber);
  return OutPinPtr(new OutPin(adress, pinNumber));
}

bool
PinFactory::verify(char adress, int pinNumber)
{
  IntSet& pinsAtThisAdress = occupiedAdressPins_[adress];
  auto insertionResult = pinsAtThisAdress.insert(pinNumber);
  const bool pinAlreadyInUse = !insertionResult.second; // or throw if true?
  return pinAlreadyInUse;
}

void
PinFactory::makeSureIsInitialized(char adress)
{
  if (occupiedAdressPins_.count(adress) == 0)
    IOPi_init(adress);
}
