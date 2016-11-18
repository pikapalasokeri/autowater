#ifndef PinHandler_hpp
#define PinHandler_hpp

#include "OutPin.hpp"
#include <vector>
#include <unordered_map>
#include <unordered_set>

class PinHandler
{
public:
  PinHandler();
  PinHandler(const PinHandler&) = delete;
  PinHandler& operator=(const PinHandler&) = delete;

  OutPin* createOutPin(char adress, int pinNumber);
 
private:
  void verify(char adress, int pinNumber);
  void makeSureIsInitialized(char adress);

  std::vector<OutPinPtr> outPins_;

  
  using IntSet = std::unordered_set<int>;
  using AdressPinsMap = std::unordered_map<char, IntSet>;
  AdressPinsMap occupiedAdressPins_;
  
  static bool alreadyCreated_;
};

#endif
