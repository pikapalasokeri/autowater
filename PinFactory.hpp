#ifndef PinFactory_hpp
#define PinFactory_hpp

#include "OutPin.hpp"
#include <unordered_map>
#include <unordered_set>

class PinFactory
{
public:
  PinFactory();
  PinFactory(const PinFactory&) = delete;
  PinFactory& operator=(const PinFactory&) = delete;

  OutPinPtr createOutPin(char adress, int pinNumber);
 
private:
  bool verify(char adress, int pinNumber);
  void makeSureIsInitialized(char adress);

  using IntSet = std::unordered_set<int>;
  using AdressPinsMap = std::unordered_map<char, IntSet>;
  AdressPinsMap occupiedAdressPins_;
  
  static bool alreadyCreated_;
};

#endif
